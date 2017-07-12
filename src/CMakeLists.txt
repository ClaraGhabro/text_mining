# Set compilation flags
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Weffc++ -pedantic -DTEXT_MININGVERSION=${TEXT_MINING__VERSION}")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Werror -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Find needed packages
#find_package(package_name REQUIRED)

# Include directories for compilation (-I)
include_directories(
  .
  #  ${package_name_INCLUDES_DIRS}
  )

# Get objects libraries from sources
#add_subdirectoru(sous_dossier)

# Create the executable with project name
add_executable(${PROJECT_NAME}
  main.cc
  #$<TARGET_OBJECT:sous_dossier_objs>
  )

#target_link_librairies(${PROJECT_NAME} #${package_name_LIBRARIES})
