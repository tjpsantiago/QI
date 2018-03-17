# -------------- get_subdirectories --------------
function(get_subdirectories result current_dir)
    file(GLOB children RELATIVE ${current_dir} ${current_dir}/*)
    set(dirlist "")
    foreach(child ${children})
        if (IS_DIRECTORY ${current_dir}/${child})
            list(APPEND dirlist ${child})
        endif(IS_DIRECTORY ${current_dir}/${child})
    endforeach(child ${children})
    set(${result} ${dirlist} PARENT_SCOPE)
endfunction(get_subdirectories result current_dir)

# ------------ get_all_subdirectories ------------
# ---- this is a recursive get_subdirectories ----
function(get_all_subdirectories result current_dir)
    file(GLOB_RECURSE children LIST_DIRECTORIES true RELATIVE ${current_dir} ${current_dir}/*)
    set(dirlist "")
    foreach(child ${children})
        if (IS_DIRECTORY ${current_dir}/${child})
            # do not include build directory created by cmake.
            # possible bug if project contains directory named 'build'
            if (NOT ${child} MATCHES "build[/]?.*")
                list(APPEND dirlist ${child})
            endif (NOT ${child} MATCHES "build[/]?.*")
        endif()
    endforeach()
    set(${result} ${dirlist} PARENT_SCOPE)
endfunction(get_all_subdirectories result current_dir)

# ------------- get_leaf_directories -------------
function(get_leaf_directories result current_dir)
    file(GLOB_RECURSE children LIST_DIRECTORIES true RELATIVE ${current_dir} ${current_dir}/*)
    set(dirlist "")
    set(branch_directories "")
    foreach(child ${children})
        if (IS_DIRECTORY ${current_dir}/${child})
            # do not include build directory created by cmake.
            # possible bug if project contains directory named 'build'
            if (NOT ${child} MATCHES "build[/]?.*")
                list(APPEND dirlist ${child})
            endif (NOT ${child} MATCHES "build[/]?.*")

            # check if previous directory is a branch directory
            if (previous_dir)
                message("searching for ${previous_dir} from ${child}")
                string(FIND ${child} ${previous_dir} output)
                # if it is, delete it from the dirlist result
                message("output = ${output}")
                if(output EQUAL 0)
                    message("removing : ${previous_dir}")
                    list(REMOVE_ITEM dirlist ${previous_dir})
                endif(output EQUAL 0)
            endif (previous_dir)

            # set previous_dir to the currently being processed directory
            set(previous_dir ${child})
        endif()
    endforeach()
    set(${result} ${dirlist} PARENT_SCOPE)
endfunction(get_leaf_directories result current_dir)
