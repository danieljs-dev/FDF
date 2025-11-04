# CHANGES

This document summarizes notable changes made to the project.

## 2025-11-04 — Migrate to MLX42 and build improvements

### Graphics backend
- Replaced minilibx-linux with MLX42 as the rendering backend.
- Updated headers: project now includes `MLX42/MLX42.h` instead of `minilibx-linux/mlx.h`.
- Refactored `t_fdf` (in `fdf.h`):
  - Added MLX42 handles: `mlx_t *mlx;` and `mlx_image_t *img;`.
  - Removed MiniLibX-specific fields: `mlx_ptr`, `win_ptr`, `img_ptr`, `img_data`, `bpp`, `size_line`, `endian`.

### Rendering pipeline
- `create_image` (in `global_utils.c`) now:
  - Creates a persistent MLX42 image once (`mlx_new_image`) and attaches it to the window (`mlx_image_to_window`).
  - Clears the image buffer with `ft_bzero` before each draw.
- `put_pixel_to_image` writes directly to the image pixel buffer as RGBA bytes (MLX42 format):
  - R: `(color >> 16) & 0xFF`
  - G: `(color >> 8) & 0xFF`
  - B: `color & 0xFF`
  - A: `0xFF`
- `draw.c` no longer calls `mlx_put_image_to_window`/`mlx_destroy_image` per frame; the image is attached once and reused.

### Events and lifecycle
- Replaced minilibx event system with MLX42 hooks:
  - Close: `mlx_close_hook(mlx, on_close, data)`.
  - Keyboard: `mlx_key_hook(mlx, on_key, data)` with `mlx_key_data_t`.
  - Scroll (mouse wheel): `mlx_scroll_hook(mlx, on_scroll, data)`.
- Cleanup now uses MLX42 lifecycle:
  - `mlx_delete_image(data->mlx, data->img)` and `mlx_terminate(data->mlx)`.

### Makefile
- Object files already configured to build into `build/obj/`.
- Switched link flags to MLX42:
  - Link against `MLX42/build/libmlx42.a` and vendored GLFW static: `MLX42/build/_deps/glfw-build/src/libglfw3.a`.
  - System libs: `-ldl -pthread -lm -lX11 -lXrandr -lXi -lXcursor` and `-Llibft -lft`.
  - Include paths: `-IMLX42/include -Ilibft`.
- `all` target now depends on `MLX42` instead of `minilibx-linux`.
- New `MLX42` target builds the library via CMake when missing:
  - `cmake -S MLX42 -B MLX42/build && cmake --build MLX42/build -j4`.
- Removed `minilibx-linux` download/build/clean steps and related flags.

### Controls and behavior
- Keyboard: arrow keys move, `+`/`-` change Z scale, `ESC` closes.
- Mouse: wheel scroll controls zoom within `[MIN_ZOOM..MAX_ZOOM]`.
- Initial zoom and centering unchanged; draw path uses the same Bresenham algorithm.

### Build and run notes
- Prerequisite: `cmake` available on the system (MLX42 build).
- Build: `make`
- Run: `./fdf <path-to-map>`, e.g. `./fdf maps/test_maps/42.fdf`.
- Linking uses the vendored GLFW built by MLX42; no separate system `-lglfw` is required.

### Known considerations
- Colors are written in RGBA byte order to match MLX42 buffer format; verify palette looks correct on your platform.
- The image buffer is cleared on every redraw for simplicity. If needed, optimize by drawing only changed regions.

---
If you have any issues with the new MLX42 setup or want to refine behavior (e.g., add more keys, improve performance, or switch to window resizing), open an issue or request in this repository.
