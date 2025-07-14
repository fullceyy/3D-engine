#include "Shader.h"

Shader::Shader(const char* vs, const char* fs) {
	std::ifstream vss;
	std::ifstream fss;

	vss.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fss.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vss.open(vs);
		fss.open(fs);
		std::stringstream vertexStreamBuffer, fragStreamBuffer;
		vertexStreamBuffer << vss.rdbuf();
		fragStreamBuffer << fss.rdbuf();
		vss.close();
		fss.close();

		vertexShader = vertexStreamBuffer.str();
		fragmentShader = fragStreamBuffer.str();
	}
	catch(std::ifstream::failure& e) {
		std::cout << "CLASS-SHADER::FAILED TO READ SHADER_TEXT_FILE!" << e.what() << "\n";
	}
	program_id = glCreateProgram();
	if (program_id == 0) {
		std::cout << "CLASS-SHADER::PROGRAM_ID FAILED TO CREATE!\n";
	}
	std::cout << vertexShader << "\n";
	std::cout << fragmentShader << "\n";
}

unsigned int Shader::CACShaders(unsigned int type) {
	unsigned int shader_id = glCreateShader(type);
	const char* path;
	if (type == GL_VERTEX_SHADER) { path = vertexShader.c_str(); }
	else if (type == GL_FRAGMENT_SHADER) { path = fragmentShader.c_str(); }
	else {
		std::cout << "SHADER-CLASS::CACSHADERS::SPECIFIED TYPE NOT SUPPORTED!\n";
		return -1;
	}

	glShaderSource(shader_id, 1, &path, NULL);
	glCompileShader(shader_id);

	int compileStatus;
	char infoLog[512];
	int shaderType;

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		std::cout << "SHADER-CLASS::CACSHADERS::COMPILE STATUS ERROR!\n";
		std::cout << "-> SHADER COMPILATION ERROR! : "
			<< (type == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER") 
			<< std::endl;
		
		std::cout << "\n" << infoLog << std::endl;
		return -1;
	}
	else {
		std::cout << "-> CACSHADERS::" << (type == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER")
			<< "LOADED / COMPILED!" << std::endl;
	}

	glGetShaderiv(shader_id, GL_SHADER_TYPE, &shaderType);
	if (shaderType == GL_VERTEX_SHADER) {
		std::cout << "vst\n";
	}
	else if (shaderType == GL_FRAGMENT_SHADER) {
		std::cout << "fst\n";
	}

	glAttachShader(program_id, shader_id);

	int linkedStatus;
	char infoLogLink[512];
	
	glLinkProgram(program_id);
	glValidateProgram(program_id);

	glGetProgramiv(program_id, GL_LINK_STATUS, &linkedStatus);
	if (!linkedStatus) {
		glGetProgramInfoLog(program_id, 512, NULL, infoLogLink);
		std::cout << "SHADER-CLASS::CACSHADERS::SHADER LINKING FAILED!\n" <<
			"-> LOG :\n" << infoLogLink << std::endl;
		return -1;
	}
	return 0;

	this->setType(type == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER");
}

void Shader::bind() const {
	// might cause some issues, not sure what kind though yet
	if (program_id != NULL) {
		glUseProgram(program_id);
	}
	else {
		std::cout << "SHADER-CLASS::BIND::BIND ATTEMPT FAILED!\n";
	}
}

void Shader::unbind() const {
	glUseProgram(0);
}


/*UNIFORMS*/
void Shader::SUvec3(const std::string& name, glm::vec3 value) const {
	glUniform3f(glGetUniformLocation(program_id, name.c_str()), value.x, value.y, value.z);
}
void Shader::SUfloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
}
void Shader::SUint(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}
void Shader::SUmat4(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}