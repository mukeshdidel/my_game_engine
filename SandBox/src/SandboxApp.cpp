#include <Soul.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>


class ExampleLayer : public soul::Layer
{
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f), m_SquarePosition(0.0f, 0.0f, 0.0f)
	{

		m_VertexArray.reset(soul::VertexArray::Create());


		float  vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		soul::Ref<soul::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(soul::VertexBuffer::Create(vertices, sizeof(vertices)));


		soul::BufferLayout layout = {
			{ soul::ShaderDataType::Float3, "a_Position" },
			{ soul::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		soul::Ref<soul::IndexBuffer> indexBuffer;
		indexBuffer.reset(soul::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(soul::VertexArray::Create());

		float  squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f

		};

		soul::Ref<soul::VertexBuffer> squareVB;
		squareVB.reset(soul::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ soul::ShaderDataType::Float3, "a_Position" },
			{ soul::ShaderDataType::Float2, "a_TexCoord" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = {
			0, 1, 2, 2, 3, 0
		};

		soul::Ref<soul::IndexBuffer> squareIB;
		squareIB.reset(soul::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;		
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
		
			out vec3 v_Position;
			out vec4 v_Color;			

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader = soul::Shader::Create("Shader1", vertexSrc, fragmentSrc);


		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;	

			uniform mat4 u_ViewProjection;	
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;
			

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";


		m_Shader2 = soul::Shader::Create("Shader2", vertexSrc2, fragmentSrc2);



		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		m_Texture = soul::Texture2D::Create("assets/textures/drogba.jpg");
		
		m_ChelseaTexture = soul::Texture2D::Create("assets/textures/chelsea.png");


		std::dynamic_pointer_cast<soul::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<soul::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}
	void OnUpdate(soul::TimeStep ts) override
	{


		if (soul::Input::IsKeyPressed(SL_KEY_A)) 
			m_CameraPosition.x -= cameraMoveSpeed * ts;
		else if (soul::Input::IsKeyPressed(SL_KEY_D))
			m_CameraPosition.x += cameraMoveSpeed * ts;
		if (soul::Input::IsKeyPressed(SL_KEY_W))
			m_CameraPosition.y += cameraMoveSpeed * ts;
		else if (soul::Input::IsKeyPressed(SL_KEY_S))
			m_CameraPosition.y -= cameraMoveSpeed * ts;


		if (soul::Input::IsKeyPressed(SL_KEY_LEFT))
			m_SquarePosition.x -= squareMoveSpeed * ts;
		else if (soul::Input::IsKeyPressed(SL_KEY_RIGHT))
			m_SquarePosition.x += squareMoveSpeed * ts;
		if (soul::Input::IsKeyPressed(SL_KEY_UP))
			m_SquarePosition.y += squareMoveSpeed * ts;
		else if (soul::Input::IsKeyPressed(SL_KEY_DOWN))
			m_SquarePosition.y -= squareMoveSpeed * ts;


		if (soul::Input::IsKeyPressed(SL_KEY_Q))
			cameraRotation += cameraRotationSpeed * ts;
		else if (soul::Input::IsKeyPressed(SL_KEY_E))
			cameraRotation -= cameraRotationSpeed * ts;


		soul::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		soul::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(cameraRotation);

		soul::Renderer::BeginScene(m_Camera);


		glm::vec4 redColor = { 0.8f, 0.2f, 0.3f, 1.0f };
		glm::vec4 blueColor = { 0.2f, 0.3f, 0.8f, 1.0f };


		std::dynamic_pointer_cast<soul::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<soul::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 20; y++)
		{
			for(int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));	
				soul::Renderer::Submit(m_Shader2, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		soul::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChelseaTexture->Bind();
		soul::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//soul::Renderer::Submit(m_Shader, m_VertexArray);

		soul::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(soul::Event& event) override
	{

	}

private:

	soul::ShaderLibrary m_ShaderLibrary;

	soul::Ref<soul::Shader> m_Shader;
	soul::Ref<soul::VertexArray> m_VertexArray;


	soul::Ref<soul::Shader> m_Shader2;
	soul::Ref<soul::VertexArray> m_SquareVA;

	soul::Ref<soul::Texture2D> m_Texture, m_ChelseaTexture;


	//soul::Ref<soul::Shader> m_TextureShader;

	soul::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float cameraMoveSpeed = 5.0f;

	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;

	glm::vec3 m_SquarePosition;
	float squareMoveSpeed = 1.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public soul::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{
	}
};

soul::Application* soul::CreateApplication()
{
	return new Sandbox();
}