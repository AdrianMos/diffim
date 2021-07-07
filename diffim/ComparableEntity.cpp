#include "ComparableEntity.h"
#include "pch.h"

ComparableEntity::ComparableEntity(const fs::path& reference,
                                   const fs::path& image,
                                   const fs::path& diff,
                                   const fs::path& mask,
                                   const fs::path& relative_path,
                                   unsigned char threshold)
    : reference(reference),
      image(image),
      diff(diff),
      mask(mask),
      relative_path(relative_path),
      threshold(threshold)
{
}
