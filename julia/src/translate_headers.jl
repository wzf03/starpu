using Clang
using Clang.LibClang.LLVM_jll

function translate_starpu_headers()
    if isfile((@__DIR__)*"/../gen/libstarpu_common.jl") && isfile((@__DIR__)*"/../gen/libstarpu_api.jl")
        return
    end

    if !isdir((@__DIR__)*"/../gen")
        mkdir((@__DIR__)*"/../gen")
    end

    debug_print("Translating StarPU headers...")

    STARPU_INCLUDE=fstarpu_include_dir()
    STARPU_HEADERS = [joinpath(STARPU_INCLUDE, header) for header in readdir(STARPU_INCLUDE) if endswith(header, ".h")]
    LIBCLANG_INCLUDE = joinpath(dirname(LLVM_jll.libclang_path), "..", "include", "clang-c") |> normpath

    clang_args = ["-I", STARPU_INCLUDE]

    for header in find_std_headers()
        push!(clang_args, "-I")
        push!(clang_args, header)
    end

    only_select_symbols = Set(["starpu_task",
                               "starpu_codelet",
                               "starpu_data_filter",
                               "starpu_tag_t",
                               "starpu_perfmodel",
                               "starpu_perfmodel_type",
                               "starpu_data_handle_t",
                               "starpu_init",
                               "starpu_data_unregister",
                               "starpu_data_partition",
                               "starpu_data_unpartition",
                               "starpu_data_get_sub_data",
                               "starpu_data_map_filters",
                               "starpu_matrix_data_register",
                               "starpu_block_data_register",
                               "starpu_vector_data_register",
                               "starpu_variable_data_register",
                               "starpu_memory_pin",
                               "starpu_memory_unpin",
                               "starpu_task_init",
                               "starpu_task_destroy",
                               "starpu_task_submit",
                               "starpu_task_wait_for_n_submitted",
                               "starpu_tag_wait",
                               "starpu_tag_declare_deps_array",
                               "starpu_task_declare_deps_array",
                               "starpu_iteration_push",
                               "starpu_iteration_pop",
                               "STARPU_CPU",
                               "STARPU_CUDA",
                               "STARPU_OPENCL",
                               "STARPU_MAIN_RAM",
                               "STARPU_NMAXBUFS"])

    wc = init(; headers = STARPU_HEADERS,
              output_file = joinpath(@__DIR__, "../gen/libstarpu_api.jl"),
              common_file = joinpath(@__DIR__, "../gen/libstarpu_common.jl"),
              clang_includes = vcat(LIBCLANG_INCLUDE, CLANG_INCLUDE),
              clang_args = clang_args,
              header_library = x->"starpu_wrapper_library_name",
              clang_diagnostics = false,
              rewriter = x->x,
              only_select_symbols = only_select_symbols,
              fields_align = Dict((:starpu_pthread_spinlock_t,:taken) => 16)
              )

    run(wc)
end
