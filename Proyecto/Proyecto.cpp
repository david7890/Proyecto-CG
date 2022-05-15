#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "modelAnim.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacion();
void animDino();
void DinoCirculo();
void animPedro();
void caminaPedro();
void animClock();
void vueloPtero();
void animCar();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(-35, 5.0, 27.5));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;
float movCamera = 0.0f;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

bool active;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotRodIzq = 0;

#define MAX_FRAMES 9
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(posX,posY,posZ),
	glm::vec3(-54, 6.9, -42.50),
	glm::vec3(posX,posY,posZ),
	glm::vec3(posX,posY,posZ)
};

glm::vec3 LightP1;




void saveFrame(void)
{

	printf("posx %f\n", posX);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;


	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;

}

void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;

}
//variables para controlar animaciones y movimientos de los objetos
//anim dino mar
bool animDinoRec = false;
bool animCola = true;
bool animCola2 = false;
bool animaAleta = true;
bool animaAleta2 = false;
bool animAletaDer = true;
bool animAletaDer2 = false;
bool animBrazo = true;
bool animBrazo2 = false;
bool animPie = true;
bool animPie2 = false;
bool animPieDer = true;
bool animPieDer2 = false;

float rotAleta = 0.0;
float rotAletaDer = 360.0;
float rotCola = 0.0;
float rotbrazo = 0.0;
float rotPie = -30.0;
float rotPieDer = 20.0;
float phiDino = 0.0;
float circx = 0.0;
float circz = 0.0;
float pospteroZ = 0.0;
float pospteroY = 0.0;
float theta = 90.0f;
float ivel = 0.5;
float radioD = 10.0;
float radioP = 38;
float rotCirculo = 0.0;
float movPedroX = 0.0;
float movPedroZ = 0.0;
float rotPedro = 0.0;

float rotManec1 = 0.0;
float rotManec2 = 0.0;
float rotpend = 0.0;
float rotpuertader = -120;
float rotpuertaIzq = 120;
float movBirdZ = -1.6;
float movAlaZ = -1.85;
float rotAlas = 0.0;
float rotAlasIzq = 0.0;
float rotAlaPtero = 0.0;
float rotAlaPteroIzq = 0.0;
float rotAlaPteroDerY = 0.0;
float rotAlaPteroIzqY = 0.0;
float rotPtero = 0.0;
float movcarX = 0.0;
float movcarZ = 0.0;
float rotcar = 0.0;
bool movpend = true;
bool movpend2 = false;
bool movpuertad = true;
bool movpuertad2 = false;
bool movbird = false;
bool movbird2 = false;
bool movAlas = false;
bool movAlas2 = false;
bool movpuertaIzq = true;
bool movpuertaIzq2 = false;
bool animPuerta = false;
bool animVuela = false;
bool animVuela2 = false;
bool animVuela3 = false;
bool animVuela4 = false;
bool animAlasPtero = true;
bool animAlasPtero2 = false;
bool movcar = false;
bool pathcar1 = true;
bool pathcar2 = false;
bool pathcar3 = false;
bool pathcar4 = false;
bool rotcar1 = false;
bool rotcar2 = false;
bool rotcar3 = false;
bool rotcar4 = false;
bool recop1 = false;
bool recop2 = false;
bool recop3 = false;
bool recop4 = false;


glm::vec3 PosIniPedro(-15, 0.3, 0.0);
glm::vec3 posIniPtero(-110, 1, -10);
glm::vec3 posIniCar(-20, -1.3, 25);
int main()
{
	// Init GLFW
	glfwInit();




	// Set all the required options for GLFW
	/*(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.frag");

	//personaje pedro
	Model PedroTorso((char*)"Models/Pedro/cuerpo.obj");
	Model PbrazoIzq((char*)"Models/Pedro/brazoIzq.obj");
	Model PbrazoDer((char*)"Models/Pedro/brazoDer.obj");
	Model PieIzq((char*)"Models/Pedro/pieIzq.obj");
	Model PieDer((char*)"Models/Pedro/pieDer.obj");
	Model Carro((char*)"Models/CarroFred/carroF.obj");
	Model Palmera((char*)"Models/Palm/palm1.obj");
	Model tv((char*)"Models/tv/tv.obj");
	Model lamp((char*)"Models/lamps/lamp2.obj");
	Model casaP((char*)"Models/Casa/casafinal.obj");
	Model pisoG((char*)"Models/Casa/piso.obj");
	Model carro2((char*)"Models/carro2/carro2.obj");
	//modelo dinosaur dorrie
	Model cuerpoD((char*)"Models/dorrie/cuerpo.obj");
	Model cola((char*)"Models/dorrie/cola.obj");
	Model pataDelDer((char*)"Models/dorrie/pataDelanteDer.obj");
	Model pataDelIzq((char*)"Models/dorrie/pataDelanteIzq.obj");
	Model PataTrasDer((char*)"Models/dorrie/pataAtrasDel.obj");
	Model pataTrasIzq((char*)"Models/dorrie/pataAtrasIzq.obj");
	Model sea((char*)"Models/dorrie/Sea.obj");
	//model cucu clock
	Model clockC((char*)"Models/clock/clock.obj");
	Model manec1((char*)"Models/clock/manecilla1.obj");
	Model manec2((char*)"Models/clock/manecilla2.obj");
	Model pendulo((char*)"Models/clock/pendulo.obj");
	Model bird((char*)"Models/clock/bird.obj");
	Model alaDer((char*)"Models/clock/alaDer.obj");
	Model alaIzq((char*)"Models/clock/alaIzq.obj");
	Model puertaDer((char*)"Models/clock/puertaDer.obj");
	Model puertaIzq((char*)"Models/clock/puertaIzq.obj");
	//pterodactyl
	Model ptero((char*)"Models/ptero/ptero.obj");
	Model pteroder((char*)"Models/ptero/pteroder.obj");
	Model pteroIzq((char*)"Models/ptero/pteroIzq.obj");

	//Objeto traslucido
	//Model objTras("Models/Cubo/Cube01.obj");

	// Build and compile our shader program

	//Inicialización de KeyFrames

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].rotInc = 0;
	}



	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};

	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();
		animDino();
		DinoCirculo();
		animPedro();
		caminaPedro();
		animClock();
		vueloPtero();
		animCar();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		//glBindTexture(GL_TEXTURE_2D, texture1);*/

		// Bind specular map
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);*/


		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp = glm::mat4(1.0f); //model temp 

		//Carga de modelo
		glm::mat4 model(1);
		//clock
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-69.5, 0, -46));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		clockC.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		//manecillas
		model = glm::translate(model, glm::vec3(-69.5, 0, -46));
		model = glm::translate(model, glm::vec3(-0.03, 8.174, 1.721));
		model = glm::rotate(model, glm::radians(rotManec1), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		manec1.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-69.5, 0, -46));
		model = glm::translate(model, glm::vec3(-0.03, 8.174, 1.72));
		model = glm::rotate(model, glm::radians(rotManec2), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		manec2.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-69.5, 0, -46));
		model = glm::translate(model, glm::vec3(-0.056, 4.05, 1.025));
		model = glm::rotate(model, glm::radians(rotpend), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pendulo.Draw(lightingShader);
		//pajaro reloj
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-69.5, 0, -46));
		model = glm::translate(model, glm::vec3(0.01, 5.208, 2.495));
		model = glm::translate(model, glm::vec3(0, 0, movBirdZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bird.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-69.5, 0, -46));
		model = glm::translate(model, glm::vec3(0.25, 5.75, 4.1));
		model = glm::translate(model, glm::vec3(0, 0, movAlaZ));
		model = glm::rotate(model, glm::radians(rotAlas), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		alaDer.Draw(lightingShader);
		//ala izq
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-69.5, 0, -46));
		model = glm::translate(model, glm::vec3(-0.190, 5.75, 4.0));
		model = glm::translate(model, glm::vec3(0, 0, movAlaZ));
		model = glm::rotate(model, glm::radians(rotAlasIzq), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		alaIzq.Draw(lightingShader);
		//puerta der clock
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-69.5, 0, -46));
		model = glm::translate(model, glm::vec3(0.485, 6.406, 2.688));
		model = glm::rotate(model, glm::radians(rotpuertader), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puertaDer.Draw(lightingShader);
		//puertaizq
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-69.5, 0, -46));
		model = glm::translate(model, glm::vec3(-0.506, 6.313, 2.7));
		model = glm::rotate(model, glm::radians(rotpuertaIzq), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puertaIzq.Draw(lightingShader);
		//pedro model 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, PosIniPedro + glm::vec3(movPedroX, -1.3, movPedroZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PedroTorso.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, PosIniPedro + glm::vec3(movPedroX, -1.3, movPedroZ));
		model = glm::translate(model, glm::vec3(0.8, 3.7, -0.281));
		model = glm::rotate(model, glm::radians(rotbrazo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PbrazoDer.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, PosIniPedro + glm::vec3(movPedroX, -1.3, movPedroZ));
		model = glm::translate(model, glm::vec3(-0.816, 3.8, -0.383));
		model = glm::rotate(model, glm::radians(rotbrazo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PbrazoIzq.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, PosIniPedro + glm::vec3(movPedroX, -1.3, movPedroZ));
		model = glm::translate(model, glm::vec3(-0.5, 2.127, 0.0));
		model = glm::rotate(model, glm::radians(rotPie), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieIzq.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, PosIniPedro + glm::vec3(movPedroX, -1.3, movPedroZ));
		model = glm::translate(model, glm::vec3(0.53, 2.07, 0.0));
		model = glm::rotate(model, glm::radians(rotPieDer), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieDer.Draw(lightingShader);
		//casa
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.0, 0.0, -30.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		casaP.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65, 0.0, -30.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pisoG.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.0, 0.0, 180));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pisoG.Draw(lightingShader);
		//sea
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13, -0.5, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sea.Draw(lightingShader);
		//carro
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-38.0, -1.3, -30.0));
		model = glm::scale(model, glm::vec3(2.6f, 2.6f, 2.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Carro.Draw(lightingShader);
		//palmera
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-73.0, -1.3, 1.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Palmera.Draw(lightingShader);
		//palm2
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-23.0, -1.3, -27));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Palmera.Draw(lightingShader);
		//carro2
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, posIniCar + glm::vec3(movcarX, 0, movcarZ));
		model = glm::rotate(model, glm::radians(rotcar), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		carro2.Draw(lightingShader);
		//lampara
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-54, 0.0, -42.50));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamp.Draw(lightingShader);
		//dinosaur dorrie 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10, 1.0, 0.0));
		model = glm::translate(model, glm::vec3(circx, 1.0, circz));
		model = glm::rotate(model, glm::radians(rotCirculo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoD.Draw(lightingShader);
		//cola rotar en y
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10, 1.0, 0.0));
		model = glm::translate(model, glm::vec3(circx, 1.0, circz));//mover en circulo
		model = glm::rotate(model, glm::radians(rotCirculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotCola), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cola.Draw(lightingShader);
		//aletas rotar
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10, 1.0, 0.0));
		model = glm::translate(model, glm::vec3(circx, 1.0, circz));//mover en circulo
		model = glm::rotate(model, glm::radians(rotCirculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotAletaDer), glm::vec3(1.0f, 0.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pataDelDer.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10, 1.0, 0.0));
		model = glm::translate(model, glm::vec3(circx, 1.0, circz));//mover en circulo
		model = glm::rotate(model, glm::radians(rotCirculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotAleta), glm::vec3(1.0f, 0.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pataDelIzq.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10, 1.0, 0.0));
		model = glm::translate(model, glm::vec3(circx, 1.0, circz));//mover en circulo
		model = glm::rotate(model, glm::radians(rotCirculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotAletaDer), glm::vec3(1.0f, 0.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PataTrasDer.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10, 1.0, 0.0));
		model = glm::translate(model, glm::vec3(circx, 1.0, circz));//mover en circulo
		model = glm::rotate(model, glm::radians(rotCirculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotAleta), glm::vec3(1.0f, 0.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pataTrasIzq.Draw(lightingShader);
		//pterodactyl
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, posIniPtero + glm::vec3(0.0, pospteroY, pospteroZ));
		model = glm::rotate(model, glm::radians(rotPtero), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ptero.Draw(lightingShader);
		view = camera.GetViewMatrix();
		//alas pterodactyl
		model = glm::mat4(1);
		model = glm::translate(model, posIniPtero + glm::vec3(0.0, pospteroY, pospteroZ));
		model = glm::translate(model, glm::vec3(1.117, 0.14, -1.17));
		model = glm::rotate(model, glm::radians(rotAlaPtero), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotAlaPteroDerY), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pteroder.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, posIniPtero + glm::vec3(0.0, pospteroY, pospteroZ));
		model = glm::translate(model, glm::vec3(-1.226, 0.18, -1.375));
		model = glm::rotate(model, glm::radians(rotAlaPteroIzq), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotAlaPteroIzqY), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pteroIzq.Draw(lightingShader);
		glBindVertexArray(0);
		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}


void animacion()
{

	//Movimiento del personaje

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].rotInc;

			i_curr_steps++;
		}

	}
	
}

void animDino() {
	if (animDinoRec) {
		if (animaAleta) {
			if (rotAleta < 20.0) {
				rotAleta += 0.1;
			}
			else {
				animaAleta = false;
				animaAleta2 = true;
			}
		}
		if (animaAleta2) {
			if (rotAleta > 0.0) {
				rotAleta -= 0.1;
			}
			else {
				animaAleta2 = false;
				animaAleta = true;
			}
		}

		if (animAletaDer) {
			//std::cout << rotAletaDer << std::endl;
			if (rotAletaDer < 360.0) {
				rotAletaDer += 0.1;
			}
			else {
				animAletaDer = false;
				animAletaDer2 = true;
			}
		}
		if (animAletaDer2) {
			//std::cout << rotAletaDer << std::endl;
			if (rotAletaDer > 340.0) {
				rotAletaDer -= 0.1;
			}
			else {
				animAletaDer2 = false;
				animAletaDer = true;
			}
		}

		if (animCola) {

			if (rotCola < 15.0) {
				rotCola += 0.1;
			}
			else {
				animCola = false;
				animCola2 = true;
			}
		}
		if (animCola2) {
			if (rotCola > -15.0) {
				rotCola -= 0.1;
			}
			else {
				animCola2 = false;
				animCola = true;
			}
		}
	}
}

void DinoCirculo() {
	if (animDinoRec) {
		float speed = 0.5;
		float phi = phiDino + (2 * speed) * glfwGetTime();
		circx = radioD * cos(phiDino - speed * glfwGetTime());
		circz = radioD * sin(phiDino - speed * glfwGetTime());
		//std::cout << rotCirculo << std::endl;
		rotCirculo = phi;
	}
}

void animPedro() {
	if (animBrazo) {
		if (rotbrazo < 20.0) {
			rotbrazo += 0.2;
		}
		else {
			animBrazo = false;
			animBrazo2 = true;
		}
	}
	else {
		if (animBrazo2) {
			if (rotbrazo > -15.0) {
				rotbrazo -= 0.2;
			}
			else {
				animBrazo2 = false;
				animBrazo = true;
			}
		}
		
	}
	if (animPie) {
		if (rotPie < 20) {
			rotPie += 0.2;
		}
		else {
			animPie = false;
			animPie2 = true;
		}
	}
	else {
		if (animPie2) {
			if (rotPie > -30) {
				rotPie -= 0.2;
			}
			else {
				animPie = true;
				animPie2 = false;
			}
		}
	}

	if (animPieDer) {
		if (rotPieDer < 20) {
			rotPieDer += 0.2;
		}
		else {
			animPieDer = false;
			animPieDer2 = true;
		}
	}
	else {
		if (animPieDer2) {
			if (rotPieDer > -30) {
				rotPieDer -= 0.2;
			}
			else {
				animPieDer = true;
				animPieDer2 = false;
			}
		}
	}
}

void caminaPedro() {
	if (recop1) {
		movPedroZ += 0.02f;
		if (movPedroZ > 20) {
			recop1 = false;
			recop2 = true;
		}
	}
	if (recop2) {
		movPedroZ -= 0.02f;
		if (movPedroZ < -25) {
			recop2 = false;
			recop1 = true;
		}
	}
	if (recop3) {
		cout << "3 posicion x:" << movPedroX << "z:´" << movPedroZ << "\n";	
		rotPedro = 90;
		movPedroX += 0.02f;
		if (movPedroX > 10) {
			recop3 = false;
			recop4 = true;
		}
	}
	if (recop4) {
		cout << "4 posicion x:" << movPedroX << "z:´" << movPedroZ << "\n";
		rotPedro = 180;
		movPedroZ -= 0.02f;
		if (movPedroZ < 0) {
			recop4 = false;
			recop1 = true;
		}
	}
}

void animClock() {
	rotManec1 += 0.4;
	rotManec2 += 0.2;
	if (movpend) {
		if (rotpend > -50) {
			rotpend -= 0.2;
		}
		else {
			movpend = false;
			movpend2 = true;
		}
	}
	else {
		if (movpend2) {
			if (rotpend < 30) {
				rotpend += 0.2;
			}
			else {
				movpend = true;
				movpend2 = false;
			}
		}
	}

	if (animPuerta) {
		if (movpuertad) {
			//abrir puerta
			rotpuertader += 0.2;
			rotpuertaIzq -= 0.2;
			if (rotpuertader > 0) {
				//puerta abierta
				movbird = true;
				movpuertad = false;
			}
		}
		if (movpuertad2) {
			//cerrar puerta
			rotpuertader -= 0.2;
			rotpuertaIzq += 0.2;
			if (rotpuertader < -120) {
				movpuertad = true;
				movpuertad2 = false;
			}
		}
		if (movbird) {
			//sacar pajaro
			movBirdZ += 0.01f;
			movAlaZ += 0.01f;
			if (movBirdZ > 0.2) {
				//mover alas
				movbird = false;
				movAlas = true;
			}
		}

		if (movAlas) {
			rotAlas += 0.2;
			rotAlasIzq -= 0.2;
			if (rotAlas > 60) {
				movAlas = false;
				movAlas2 = true;
			}
		}

		if (movAlas2) {
			rotAlas -= 0.2;
			rotAlasIzq += 0.2;
			if (rotAlas < 0) {
				movAlas2 = false;
				movbird2 = true;
			}
		}

		if (movbird2) {
			//meter pajaro
			movBirdZ -= 0.01;
			movAlaZ -= 0.01;
			if (movBirdZ < -1.6) {
				movbird2 = false;
				movpuertad2 = true;
			}
		}
	}
}

void vueloPtero() {
	
	if (animVuela) {
		pospteroZ = radioP * cos(theta - (ivel * glfwGetTime()));
		pospteroY = radioP * sin(theta - (ivel * glfwGetTime()));
		float posY = posIniPtero.y + pospteroY;
		float posZ = posIniPtero.z + pospteroZ;
		std::cout << "pos z: " << posZ << std::endl;
		std::cout << "pos y: " << posY << std::endl;

		if (posY < 1 && posZ > 27.9 ) {
			animVuela = false;
			animVuela2 = true;
		}

	}

	if (animVuela2) {
		//rotar cuerpo y alas
		rotPtero += 0.3;
		rotAlaPteroDerY += 0.3;
		rotAlaPteroIzqY += 0.3;
		if (rotPtero > 180) {
			animVuela2 = false;
			animVuela3 = false;
		}
	}

	if (animVuela3) {
		theta = -90.0f;
		pospteroZ = radioP * cos(theta - (ivel * glfwGetTime()));
		pospteroY = radioP * sin(theta - (ivel * glfwGetTime()));

	}

	if (animAlasPtero) {
		rotAlaPtero += 0.1;
		rotAlaPteroIzq -= 0.1;
		if (rotAlaPtero > 40) {
			animAlasPtero = false;
			animAlasPtero2 = true;
		}
	}

	if (animAlasPtero2) {
		rotAlaPtero -= 0.1;
		rotAlaPteroIzq += 0.1;
		if (rotAlaPtero < -30) {
			animAlasPtero = true;
			animAlasPtero2 = false;
		}
	}
}

void animCar() {
	if (movcar) {
		if (pathcar1) {
			rotcar = 0.0f;
			movcarZ += 0.03f;
			if (movcarZ > 75) {
				pathcar1 = false;
				rotcar1 = true;
			}
		}

		if (rotcar1) {
			//rotar carro 
			rotcar -= 0.05;
			if (rotcar < -90) {
				rotcar1 = false;
				pathcar2 = true;
			}
		}

		if (pathcar2) {
			movcarX -= 0.03;
			if (movcarX < -70) {
				pathcar2 = false;
				rotcar2 = true;
			}
		}

		if (rotcar2) {
			rotcar -= 0.05;
			if (rotcar < -180) {
				rotcar2 = false;
				pathcar3 = true;
			}
		}

		if (pathcar3) {
			movcarZ -= 0.03;
			if (movcarZ < 25) {
				pathcar3 = false;
				rotcar3 = true;
			}
		}
		if (rotcar3) {
			rotcar -= 0.05;
			if (rotcar < -270) {
				rotcar3 = false;
				pathcar4 = true;
			}
		}
		if (pathcar4) {
			movcarX += 0.03;
			if (movcarX > -20) {
				pathcar4 = false;
				rotcar4 = true;
			}
		}
		if (rotcar4) {
			rotcar -= 0.05;
			if (rotcar < -360) {
				rotcar4 = false;
				pathcar1 = true;
			}
		}

	}
	
}
// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}

	if (keys[GLFW_KEY_K])
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

		rot = -25.0f;//Variable que maneja el giro de la camara

	}


	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
			LightP1 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	if (keys[GLFW_KEY_1])
	{

		movCamera = 0.01f;//Manda una velocidad de 0.01 a la camara automatica

	}

	if (keys[GLFW_KEY_2])
	{
		if (rotRodIzq < 80.0f)
			rotRodIzq += 1.0f;

	}

	if (keys[GLFW_KEY_3])
	{
		if (rotRodIzq > -45)
			rotRodIzq -= 1.0f;

	}



	//Mov Personaje
	if (keys[GLFW_KEY_H])
	{
		posZ += 1;
	}

	if (keys[GLFW_KEY_Y])
	{
		posZ -= 1;
	}

	if (keys[GLFW_KEY_G])
	{
		posX -= 1;
	}

	if (keys[GLFW_KEY_J])
	{
		posX += 1;
	}

	if (keys[GLFW_KEY_I]) {
		animPuerta = true;
	}
	if (keys[GLFW_KEY_O]) {
		animDinoRec = true;
	}
	if (keys[GLFW_KEY_P]) {
		recop1 = true;
	}
	if (keys[GLFW_KEY_E]) {
		animVuela = true;
	}
	if (keys[GLFW_KEY_R]) {
		movcar = true;
	}
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

}