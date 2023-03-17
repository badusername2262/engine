#pragma once

#include <vector>
#include <GL/glew.h>

#include "buffer.h"

namespace Graphics {

	class VertexArray
	{
	private:
		GLuint arrayID;
		std::vector<Buffer*> buffers;
	public:
		VertexArray() { glGenVertexArrays(1, &arrayID); }
		~VertexArray() {
			for (int i = 0; i < buffers.size(); i++)
				delete buffers[i];
		}

		void addBuffer(Buffer* buffer, GLuint index)
		{
			bind();
			buffer->bind();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			buffer->unbind();
			unbind();
		}
		void bind() const { glBindVertexArray(arrayID); }
		void unbind() const { glBindVertexArray(0); }
	};

}