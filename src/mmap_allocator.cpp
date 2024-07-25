#include <mmap_allocator.h>
void SetDefault(std::string filename) {
  default_allocator = static_cast<void *>(Allocator<char>::New(filename));
}
void FreeDefault() { delete static_cast<Allocator<char> *>(default_allocator); }
