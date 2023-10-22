#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <mizumi/shader.h>
#include <mizumi/texture.h>
#include <mizumi/mesh.h>

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	constexpr int window_width = 600;
	constexpr int window_height = 400;
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "mizumi example", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "glewInit() failed!\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	miz::shader program("vertex.glsl", "fragment.glsl");

	miz::texture texture("container.png");

	const std::vector<miz::vertex> vertices = {
		// Position						// Color					// Texcoord				// normal
	{	glm::vec3(-0.5f,  0.5f,  0.0f),	glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, -1.f), },
	{	glm::vec3(-0.5f, -0.5f,  0.0f),	glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, -1.f), },
	{	glm::vec3( 0.5f, -0.5f,  0.0f),	glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, -1.f), },
	{	glm::vec3( 0.5f,  0.5f,  0.0f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, -1.f), },
	};
	const std::vector<GLuint> indices = {
		0, 1, 2,
		0, 2, 3,
	};
	miz::mesh mesh(vertices, indices);

	glm::mat4 model_matrix(1.f);
	model_matrix = glm::rotate(model_matrix, glm::radians(30.f), glm::vec3(0.f, 1.f, 0.f));
	model_matrix = glm::rotate(model_matrix, glm::radians(25.f), glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f) + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 projection_matrix = glm::perspective(glm::radians(90.f), static_cast<float>(window_width) / window_height, 0.1f, 1000.f);
	glm::vec3 light(0.f, 0.f, 3.f);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			model_matrix = glm::rotate(model_matrix, glm::radians(1.5f), glm::vec3(0.f, 1.f, 0.f));
		}

		glClearColor(0.4823529412f, 0.6588235294f, 0.3411764706f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glUseProgram(program);
		glUniform1i(glGetUniformLocation(program, "texture0"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, GL_FALSE, glm::value_ptr(projection_matrix));
		glUniform3fv(glGetUniformLocation(program, "light"), 1, glm::value_ptr(light));

		glBindVertexArray(mesh);
		mesh.draw();
		glBindVertexArray(0);

		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glfwSwapBuffers(window);
		glFlush();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}