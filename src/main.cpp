#include <cstdio>

#include <iostream>
#include <memory>
#include <exception>

#include "omgl.hpp"

static bool run_loop = true;

omgl::Shader* vertex_shader_ptr = nullptr;
omgl::Program* program_ptr = nullptr;

static void EventHandler(omgl::Context&, const omgl::Context::Event& e)
{
  switch (e.type)
  {
    case omgl::Context::Event::Type::Close:
    run_loop = false;
    break;

    case omgl::Context::Event::Type::Press:
    if (vertex_shader_ptr)
    {
      vertex_shader_ptr->Reload();
      program_ptr->AttachShader(*vertex_shader_ptr);
      program_ptr->Link();
      program_ptr->Use();
    }
    break;

    default:
    break;
  }
}

// The whole rendering routine here
static inline void RenderBackBuffer()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
  auto& clock_driver = omgl::ClockDriver::instance();
  auto& file_driver = omgl::FileDriver::instance();

  omgl::Context ctx(300, 300);
  ctx.MakeCurrent();
  ctx.event_handler = EventHandler;

  omglGetAllProcAddresses();
  
  omgl::Shader vertex_shader(
    file_driver.Rel("../data/vertex.glsl"),
    omgl::Shader::Type::Vertex
  );
  omgl::Shader fragment_shader(
    file_driver.Rel("../data/fragment.glsl"),
    omgl::Shader::Type::Fragment
  );

  omgl::Program program;
  program.AttachShader(vertex_shader);
  program.AttachShader(fragment_shader);
  if (!program.Link())
  {
    std::cout << "Failed to link\n";
    return 1;
  }
  program.Use();
  
  float v[] =
  {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };  

  GLuint vbo, vao;
  glGenBuffers(1, &vbo);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  while (run_loop)
  {
    ctx.HandleEvents();

    RenderBackBuffer();
    ctx.SwapBuffers();

    clock_driver.SleepRemainder();
  }

  return 0;
}
