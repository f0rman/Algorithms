# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( CGAL_ )

cmake_minimum_required(VERSION 2.6.2)
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" VERSION_GREATER 2.6)
  if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}" VERSION_GREATER 2.8.3)
    cmake_policy(VERSION 2.8.4)
  else()
    cmake_policy(VERSION 2.6)
  endif()
endif()

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  create_single_source_cgal_program( "AlmostAntenna.cpp" )
  create_single_source_cgal_program( "antenna.cpp" )
  create_single_source_cgal_program( "bistro.cpp" )
  create_single_source_cgal_program( "collisions.cpp" )
  create_single_source_cgal_program( "Diets.cpp" )
  create_single_source_cgal_program( "firsthit.cpp" )
  create_single_source_cgal_program( "germs.cpp" )
  create_single_source_cgal_program( "graypes.cpp" )
  create_single_source_cgal_program( "H1N1.cpp" )
  create_single_source_cgal_program( "hikingmaps.cpp" )
  create_single_source_cgal_program( "hit.cpp" )
  create_single_source_cgal_program( "inball.cpp" )
  create_single_source_cgal_program( "maximize.cpp" )
  create_single_source_cgal_program( "portfolios.cpp" )
  create_single_source_cgal_program( "surveillance.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

