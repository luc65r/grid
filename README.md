# grid

A grid layout for [river](https://github.com/riverwm/river).

It follows this pattern:
```
┌───────────┐ ┌─────┬─────┐
│           │ │     │     │
│     1     │ │  1  │  2  │
│           │ │     │     │
└───────────┘ └─────┴─────┘
┌───────────┐ ┌─────┬─────┐ ┌─────┬─────┐ ┌───┬───┬───┐
│     1     │ │  1  │  2  │ │  1  │  2  │ │ 1 │ 2 │ 3 │
├─────┬─────┤ ├─────┼─────┤ ├───┬─┴─┬───┤ ├───┼───┼───┤
│  2  │  3  │ │  3  │  4  │ │ 3 │ 4 │ 5 │ │ 4 │ 5 │ 6 │
└─────┴─────┘ └─────┴─────┘ └───┴───┴───┘ └───┴───┴───┘
```

## Development status

- usable
- no error handling (only asserts)
- no ressource deallocation
- no support for gaps/padding
- may have 1 px gaps due to integer division
