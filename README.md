# grid

A grid layout for [river](https://github.com/riverwm/river).

It follows this pattern:
```
┌───────────┐ ┌─────┬─────┐
│           │ │     │     │
│           │ │     │     │
│           │ │     │     │
└───────────┘ └─────┴─────┘
┌───────────┐ ┌─────┬─────┐ ┌─────┬─────┐ ┌───┬───┬───┐
│           │ │     │     │ │     │     │ │   │   │   │
├─────┬─────┤ ├─────┼─────┤ ├───┬─┴─┬───┤ ├───┼───┼───┤
│     │     │ │     │     │ │   │   │   │ │   │   │   │
└─────┴─────┘ └─────┴─────┘ └───┴───┴───┘ └───┴───┴───┘
```

## Development status

- usable
- no error handling (only asserts)
- no ressource deallocation
- no support for gaps/padding
- may have 1 px gaps due to integer division
