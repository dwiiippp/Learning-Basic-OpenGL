project(
    'first_opengl_project',
    ['c', 'cpp'],
    version : '1.0'
)


glfw = declare_dependency(

    include_directories: include_directories(
        'include',
        'src'
    ),


    link_args:
    [
        '-Llibraries',
        '-lglfw3',
        '-lopengl32',
        '-lgdi32'
    ]

)



executable(

    'first_opengl_project',

    [
        'src/main.cpp',
        'src/glad.c',
        'src/ShaderManajer.h',
        'src/ShaderManajer.cpp'
    ],


    dependencies:
    glfw

)