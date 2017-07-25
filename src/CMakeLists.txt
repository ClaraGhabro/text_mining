# Set compilation flags
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Weffc++ -pedantic -DTEXT_MININGVERSION=${TEXT_MINING__VERSION}")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

# Include directories for compilation (-I)
include_directories(
  .
  )

# Get objects libraries from sources
#add_subdirectoru(sous_dossier)
add_subdirectory(trie)
add_subdirectory(compiler)
add_subdirectory(app)

# Create the executable with project name
add_executable(TextMiningCompiler
  #  $<TARGET_OBJECTS:sous_dossier_objs>
  $<TARGET_OBJECTS:trie_objs>
  $<TARGET_OBJECTS:compiler_objs>
  )

add_executable(TextMiningApp
  $<TARGET_OBJECTS:trie_objs>
  $<TARGET_OBJECTS:app_objs>
  )

