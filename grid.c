#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>

#include "river-layout-v3.h"

static struct wl_display *wl_display;
static struct wl_registry *wl_registry;
static struct river_layout_manager_v3 *layout_manager;
static struct wl_list outputs;

struct output {
    uint32_t name;
    struct wl_output *wl_output;
    struct river_layout_v3 *layout;
    struct wl_list link;
};

static void layout_handle_namespace_in_use(
    void *data,
    struct river_layout_v3 *layout
) {
    fprintf(stderr, "namespace already in use\n");
    exit(1);
}

static void layout_handle_layout_demand(
    void *data,
    struct river_layout_v3 *layout,
    uint32_t view_count,
    uint32_t usable_width,
    uint32_t usable_height,
    uint32_t tags,
    uint32_t serial
) {
    struct output *output = data;
    assert(output->layout == layout);

    uint32_t row_count = 1;
    while (row_count * (row_count + 1) < view_count)
        row_count++;
    assert(row_count * (row_count - 1) < view_count
           && view_count <= row_count * (row_count + 1));

    uint32_t height = usable_height / row_count;

    for (uint32_t row = 0; row < row_count; row++) {
        uint32_t column_count = view_count / (row_count - row);
        uint32_t width = usable_width / column_count;
        for (uint32_t column = 0; column < column_count; column++) {
            int32_t x = column * width;
            int32_t y = row * height;
            river_layout_v3_push_view_dimensions(layout, x, y, width, height, serial);
            view_count--;
        }
    }

    assert(view_count == 0);

    river_layout_v3_commit(layout, "grid", serial);
}

static void layout_handle_user_command(
    void *data,
    struct river_layout_v3 *layout,
    const char *command
) {
    struct output *output = data;
    printf("user command: %s\n", command);
}

static const struct river_layout_v3_listener layout_listener = {
    .namespace_in_use = layout_handle_namespace_in_use,
    .layout_demand = layout_handle_layout_demand,
    .user_command = layout_handle_user_command,
};

static void registry_handle_global(
    void *data,
    struct wl_registry *registry,
    uint32_t name,
    const char *interface,
    uint32_t version
) {
    if (strcmp(interface, river_layout_manager_v3_interface.name) == 0) {
        layout_manager = wl_registry_bind(registry, name, &river_layout_manager_v3_interface, 1);
        assert(layout_manager != NULL);
    } else if (strcmp(interface, wl_output_interface.name) == 0) {
        struct output *output = malloc(sizeof *output);
        assert(output != NULL);
        output->name = name;

        output->wl_output = wl_registry_bind(registry, name, &wl_output_interface, 3);
        assert(output->wl_output != NULL);

        output->layout = river_layout_manager_v3_get_layout(layout_manager, output->wl_output, "grid");
        assert(output->layout != NULL);
        river_layout_v3_add_listener(output->layout, &layout_listener, output);

        wl_list_insert(&outputs, &output->link);
    }
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_handle_global,
};

int main(void) {
    wl_list_init(&outputs);

    wl_display = wl_display_connect(NULL);
    assert(wl_display != NULL);
    wl_registry = wl_display_get_registry(wl_display);
    assert(wl_registry != NULL);
    wl_registry_add_listener(wl_registry, &registry_listener, NULL);

    wl_display_roundtrip(wl_display);
    while (wl_display_dispatch(wl_display) != -1)
        ;
    
    return 0;
}
