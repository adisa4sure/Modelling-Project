file(REMOVE_RECURSE
  "../lib/liblibFingerPrinth.pdb"
  "../lib/liblibFingerPrinth.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/libFingerPrinth.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
