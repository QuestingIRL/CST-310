//frame.cpp
//g++ couch.cpp -o couch -lGLEW -lGL -lGLU -lglut
/***********************
 * 1. Include Directives
 ***********************/
#include <GL/glew.h>    // Include GLEW before GLUT
#include <GL/glut.h>    // GLUT, includes glu.h and gl.h
#include <iostream>
#include <string>
#include <cmath>        // For mathematical operations
#include <iomanip>      // For formatting
#include <sstream>      // For string streams
#include <vector>       // For dynamic arrays
#include "utilities.h"
#include "leftCouch.cpp"
#include "midCouch.cpp"
#include "rightCouch.cpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  // Include stb_image for image loading

/*****************************
 * 2. Macro Definitions and Constants
 *****************************/
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 700;

// Colors (RGB format)
const float FRAME_COLOR[3] = {0.5f, 0.5f, 0.5f};         // Gray
const float FILL_COLOR[3] = {0.6549f, 0.5451f, 0.4039f}; // #a78b67
const float AXIS_COLOR[3] = {0.0f, 0.0f, 0.0f};           // Black
const float PURPLE_COLOR[3] = {0.5f, 0.0f, 0.5f};         // Purple
const float BLUE_COLOR[3] = {0.0f, 0.0f, 1.0f};            // Blue
const float WHITE_COLOR[3] = {1.0f, 1.0f, 1.0f};           // White
const float LPURPLE_COLOR[3] = {0.847f, 0.749f, 0.847f};

// Gradient color for the top half of the frame
const float GRADIENT_COLOR[3] = {0.776f, 0.796f, 0.812f}; // rgba(198,203,207,255)
// Gradient split point (y-coordinate where the gradient starts)
const float GRADIENT_SPLIT_Y = -0.5f; // Adjust this value as needed

// Tick properties
const float TICK_LENGTH = 0.02f;    // Length of tick marks
const float TICK_INTERVAL = 0.1f;   // Interval between ticks
struct GradientRectangle {
    float rotation_angle;   // Rotation angle in degrees
    float translate_x;      // Translation along the X-axis
    float translate_y;      // Translation along the Y-axis
    bool isHorizontal;      // Gradient direction: true for horizontal, false for vertical
};

std::vector<GradientRectangle> gradientRectangles; // Vector to store gradient rectangles
/*****************************
 * 3. Class Definitions
 *****************************/
class Rectangle {
public:
    // Constructor to initialize rectangle properties
    Rectangle(float centerX, float centerY, float width, float height, const float color[3])
        : centerX(centerX), centerY(centerY), width(width), height(height)
    {
        this->color[0] = color[0];
        this->color[1] = color[1];
        this->color[2] = color[2];
    }

    // Method to draw the rectangle
    void draw() const {
        glColor3fv(color); // Set the rectangle color

        // Calculate half-width and half-height
        float half_width = width / 2.0f;
        float half_height = height / 2.0f;

        // Calculate vertices based on center position
        float left = centerX - half_width;
        float right = centerX + half_width;
        float bottom = centerY - half_height;
        float top = centerY + half_height;

        // Draw the rectangle using GL_QUADS
        glBegin(GL_QUADS);
            glVertex2f(left,  top);    // Top-left
            glVertex2f(left,  bottom); // Bottom-left
            glVertex2f(right, bottom); // Bottom-right
            glVertex2f(right, top);    // Top-right
        glEnd();
    }

private:
    float centerX;
    float centerY;
    float width;
    float height;
    float color[3];
};

/*****************************
 * 4. Global Variables
 *****************************/
std::vector<Rectangle> rectangles; // Vector to store all rectangles
GLuint fillTexture;                // Texture ID for the fill rectangle
GLuint floorTexture;  // New texture for the floor

/*****************************
 * 5. Function Prototypes
 *****************************/
void initGL();
void renderBitmapString(float x, float y, void *font, const std::string &str);
std::string formatFloat(float number);
// void drawCoordinateAxes(); // Commented out as per original code
void drawFadingRectangle(float centerX, float centerY, float width, float height, bool horizontal = true);
void drawRectangles();
void display();
void reshape(int width, int height);

/*****************************
 * 6. Function Implementations
 *****************************/

// Initialization function
void initGL()
{
    // Set the background color to white
    glClearColor(.7098f, .733f, .7254f, 1.0f);

    // Initialize rectangles
    rectangles.emplace_back(-0.1f,  -0.05f,  0.07f, 0.15f, PURPLE_COLOR); // Adjusted Purple Rectangle
    rectangles.emplace_back(-0.2f, -0.07f, 0.07f, 0.15f, BLUE_COLOR);
    rectangles.emplace_back(-0.23f,  0.2f,  0.07f, 0.15f, PURPLE_COLOR); // Adjusted Purple Rectangle
    rectangles.emplace_back(0.05f,  0.05f,  0.07f, 0.15f, WHITE_COLOR);
    rectangles.emplace_back(0.11f,  -0.15f,  0.07f, 0.15f, LPURPLE_COLOR);
    rectangles.emplace_back(0.19f,  0.04f,  0.07f, 0.15f, WHITE_COLOR);
    // Initialize gradient rectangles
    // 1. Under First Purple Rectangle
    GradientRectangle gr1 = {0.0f, -0.1f, -0.057f, true};
    gradientRectangles.push_back(gr1);

    // 2. Under Blue Rectangle
    GradientRectangle gr2 = {0.0f, -0.2f, -0.077f, true};
    gradientRectangles.push_back(gr2);

    // 3. Under Second Purple Rectangle
    GradientRectangle gr3 = {0.0f, -0.23f, 0.193f, true};
    gradientRectangles.push_back(gr3);

    // 4. Under Light Purple Rectangle
    GradientRectangle gr4 = {0.0f, 0.11f, -0.159f, true};
    gradientRectangles.push_back(gr4);

    // 5. Under Second White Rectangle
    GradientRectangle gr5 = {0.0f, 0.19f, 0.03f, true};
    gradientRectangles.push_back(gr5);

    // 6. Under First White Rectangle
    GradientRectangle gr6 = {0.0f, 0.05f, 0.043f, true};
    gradientRectangles.push_back(gr6);
    // **Load the Texture**
    int width, height, nrChannels;
    unsigned char *data = stbi_load("cork.v1.jpg", &width, &height, &nrChannels, 3);
    
    if (data)
    {
        std::cout << "Image loaded successfully: width=" << width << " height=" << height << " channels=" << nrChannels << std::endl;

        glGenTextures(1, &fillTexture);
        glBindTexture(GL_TEXTURE_2D, fillTexture);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // Repeat horizontally
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   // Repeat vertically
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification

        // Determine image format (forcing GL_RGB because we loaded 3 channels)
        GLenum format = GL_RGB;

        // Upload texture to GPU
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Failed to load texture: cork1.v1.jpg. Reason: " << stbi_failure_reason() << std::endl;
    }
     int floorWidth, floorHeight, floorChannels;
    unsigned char *floorData = stbi_load("floor.v1.jpg", &floorWidth, &floorHeight, &floorChannels, 3);

    if (floorData)
    {
        std::cout << "Floor image loaded successfully: width=" << floorWidth 
                  << " height=" << floorHeight << " channels=" << floorChannels << std::endl;

        glGenTextures(1, &floorTexture);
        glBindTexture(GL_TEXTURE_2D, floorTexture);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

        // Determine image format (assuming RGB)
        GLenum format = GL_RGB;

        // Upload texture to GPU
        glTexImage2D(GL_TEXTURE_2D, 0, format, floorWidth, floorHeight, 0, format, GL_UNSIGNED_BYTE, floorData);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(floorData);
    }
    else
    {
        std::cerr << "Failed to load floor texture: floor_image.jpg. Reason: " 
                  << stbi_failure_reason() << std::endl;
    }
}

// Helper function to render bitmap strings
void renderBitmapString(float x, float y, void *font, const std::string &str)
{
    glRasterPos2f(x, y);
    for (const char &c : str)
    {
        glutBitmapCharacter(font, c);
    }
}

// Helper function to format float to string with one decimal place
std::string formatFloat(float number)
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(1) << number;
    std::string str = ss.str();

    // Remove trailing ".0" for whole numbers
    if (str.find(".0") != std::string::npos)
    {
        str = str.substr(0, str.size() - 2);
    }

    return str;
}

// Function to draw all rectangles stored in the global vector
void drawWhite() {
    glPushMatrix();  // Save the current transformation matrix

    // Apply fixed scaling (adjust these values as needed)
    glScalef(1.0f, 0.09f, 1.0f);  // Default scaling

    // Apply fixed translation (adjust these values as needed)
    glTranslatef(0.2f, 10.7f, 0.0f);  // Translate the rectangle

    // Begin drawing the rectangle with a more subtle gradient
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // **Top-Left Vertex**: White color
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // White color with full opacity
        glVertex2f(-1.5f, 0.5f);  // Top-left

        // **Top-Right Vertex**: White color
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // White color with full opacity
        glVertex2f(1.0f, 0.5f);   // Top-right

        // **Bottom-Right Vertex**: Intermediate gradient color (lighter shade)
        glColor4f(0.85f, 0.86f, 0.86f, 1.0f);  // Lighter gradient color for a subtle effect
        glVertex2f(1.0f, -0.2f);  // Lower position to reduce gradient intensity

        // **Bottom-Left Vertex**: Intermediate gradient color (lighter shade)
        glColor4f(0.85f, 0.86f, 0.86f, 1.0f);  // Lighter gradient color for a subtle effect
        glVertex2f(-1.5f, -0.2f); // Lower position to reduce gradient intensity

    glEnd();  // End of quadrilateral definition

    // Start a second rectangle for the darker gradient at the bottom
    glBegin(GL_QUADS);

        // **Top-Left Vertex**: Intermediate gradient color (lighter shade)
        glColor4f(0.85f, 0.86f, 0.86f, 1.0f);  // Lighter gradient color
        glVertex2f(-1.5f, -0.2f);  // Top-left

        // **Top-Right Vertex**: Intermediate gradient color (lighter shade)
        glColor4f(0.85f, 0.86f, 0.86f, 1.0f);  // Lighter gradient color
        glVertex2f(1.0f, -0.2f);   // Top-right

        // **Bottom-Right Vertex**: Gradient color (darker)
        glColor4f(0.7098f, 0.733f, 0.7254f, 1.0f);  // Original gradient color
        glVertex2f(1.0f, -0.5f);  // Bottom-right

        // **Bottom-Left Vertex**: Gradient color (darker)
        glColor4f(0.7098f, 0.733f, 0.7254f, 1.0f);  // Original gradient color
        glVertex2f(-1.5f, -0.5f); // Bottom-left

    glEnd();  // End of second quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}
void baseboard() {
    // Define the RGBA color (24, 24, 26, 255)
    unsigned char R = 24;   // Red component (0-255)
    unsigned char G = 24;   // Green component (0-255)
    unsigned char B = 26;   // Blue component (0-255)
    unsigned char A = 255;  // Alpha component (0-255)

    // Convert RGBA to normalized RGB (0.0f - 1.0f)
    float colorR = R / 255.0f;
    float colorG = G / 255.0f;
    float colorB = B / 255.0f;

    glPushMatrix();  // Save the current transformation matrix

    // Apply fixed scaling (same as in drawWhite)
    glScalef(1.0f, 0.09f, 1.0f);  // Default scaling

    // Apply fixed translation (same as in drawWhite)
    glTranslatef(0.2f, -6.5f, 0.0f);  // Translate the rectangle

    // Set the RGBA color for the rectangle
    glColor4f(colorR, colorG, colorB, A / 255.0f);  // Set the color with full opacity

    // Begin drawing the rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Define the four vertices of the rectangle (same as in drawWhite)
        glVertex2f(-1.5f, 0.5f);  // Top-left
        glVertex2f(1.0f, 0.5f);   // Top-right
        glVertex2f(1.0f, -0.5f);  // Bottom-right
        glVertex2f(-1.5f, -0.5f); // Bottom-left

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}
void drawFloor() {
    glPushMatrix();  // Save the current transformation matrix

    // Apply fixed scaling (same as in drawWhite)
    glScalef(1.0f, 1.0f, 1.0f);  // Default scaling

    // Apply fixed translation (same as in drawWhite)
    glTranslatef(0.2f, -1.13f, 0.0f);  // Translate the rectangle

    if (floorTexture)
    {
        glEnable(GL_TEXTURE_2D);                  // Enable 2D texturing
        glBindTexture(GL_TEXTURE_2D, floorTexture); // Bind the floor texture

        glColor3f(1.0f, 1.0f, 1.0f); // Set color to white to display the texture's true colors

        glBegin(GL_QUADS);  // Start defining a quadrilateral
            // Define texture coordinates and vertex positions
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(-1.5f, 0.5f);  // Top-left

            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(1.0f, 0.5f);   // Top-right

            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(1.0f, -0.5f);  // Bottom-right

            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(-1.5f, -0.5f); // Bottom-left
        glEnd();  // End of quadrilateral definition

        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
        glDisable(GL_TEXTURE_2D);        // Disable texturing
    }
    else
    {
        // If texture failed to load, fallback to solid color
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);  // Red color with full opacity

        glBegin(GL_QUADS);  // Start defining a quadrilateral
            // Define the four vertices of the rectangle
            glVertex2f(-1.5f, 0.5f);  // Top-left
            glVertex2f(1.0f, 0.5f);   // Top-right
            glVertex2f(1.0f, -0.5f);  // Bottom-right
            glVertex2f(-1.5f, -0.5f); // Bottom-left
        glEnd();  // End of quadrilateral definition
    }

    glPopMatrix();  // Restore the previous transformation matrix
}


void drawRectangles()
{
    for (const auto& rect : rectangles)
    {
        rect.draw();
    }
}
void drawFadingRectangle(float centerX, float centerY, float width, float height, bool horizontal)
{
    // Define colors
    const float BLACK_COLOR[3] = {0.0f, 0.0f, 0.0f};
    const float GRAY_COLOR[3] = {0.5f, 0.5f, 0.5f};

    // Calculate half-width and half-height
    float half_width = width / 2.0f;
    float half_height = height / 2.0f;

    // Calculate split point
    float split = 0.0f; // Center

    // Draw left quad: gray to black
    glBegin(GL_QUADS);
        if (horizontal)
        {
            // Horizontal gradient: left (gray) to center (black)
            glColor3fv(GRAY_COLOR); // Left color
            glVertex2f(-half_width, -half_height);
            glVertex2f(-half_width, half_height);

            glColor3fv(BLACK_COLOR); // Center color
            glVertex2f(0.0f, half_height);
            glVertex2f(0.0f, -half_height);
        }
        else
        {
            // Vertical gradient: bottom (gray) to center (black)
            glColor3fv(GRAY_COLOR); // Bottom color
            glVertex2f(-half_width, -half_height);
            glVertex2f(half_width, -half_height);

            glColor3fv(BLACK_COLOR); // Center color
            glVertex2f(half_width, 0.0f);
            glVertex2f(-half_width, 0.0f);
        }
    glEnd();

    // Draw right quad: black to gray
    glBegin(GL_QUADS);
        if (horizontal)
        {
            // Horizontal gradient: center (black) to right (gray)
            glColor3fv(BLACK_COLOR); // Center color
            glVertex2f(0.0f, -half_height);
            glVertex2f(0.0f, half_height);

            glColor3fv(GRAY_COLOR); // Right color
            glVertex2f(half_width, half_height);
            glVertex2f(half_width, -half_height);
        }
        else
        {
            // Vertical gradient: center (black) to top (gray)
            glColor3fv(BLACK_COLOR); // Center color
            glVertex2f(-half_width, 0.0f);
            glVertex2f(half_width, 0.0f);

            glColor3fv(GRAY_COLOR); // Top color
            glVertex2f(half_width, half_height);
            glVertex2f(-half_width, half_height);
        }
    glEnd();
}
void behind() {
    // Define the RGBA color (5, 6, 12, 255)
    unsigned char R = 5;    // Red component (0-255)
    unsigned char G = 6;    // Green component (0-255)
    unsigned char B = 12;   // Blue component (0-255)
    unsigned char A = 255;  // Alpha component (0-255)

    // Convert RGBA to normalized RGB (0.0f - 1.0f)
    float colorR, colorG, colorB;
    convertRGBA(colorR, colorG, colorB, R, G, B, A);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: scaling if necessary (adjust as needed)
    glScalef(1.0f, 1.0f, 1.0f);  // Default scaling, can be adjusted

    // Set the RGBA color for the rectangle
    glColor4f(colorR, colorG, colorB, A / 255.0f);  // Include alpha channel

    // Begin drawing the rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Define the four vertices of the rectangle
        glVertex2f(-0.475f, 0.5f);  // Top-left
        glVertex2f(0.4f, 0.522f);   // Top-right
        glVertex2f(0.53f, -0.5f);  // Bottom-right
        glVertex2f(-0.52f, -0.5f); // Bottom-left

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}
// Display callback function
// Display callback function
void display()
{
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Coordinate system: Left, Right, Bottom, Top
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Switch to modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    baseboard();
    drawFloor();

    // Disable lighting for simplicity
    glDisable(GL_LIGHTING);
    /*****************************
     * Apply Translation to Move Elements Upward
     *****************************/
    glPushMatrix(); // Save the current matrix

    // Apply translation: move everything up by 0.2 units on the Y-axis
    glTranslatef(0.06f, 0.35f, 0.0f);
    glScalef(1.3f, 1.0f, 1.0f);          // Scale down the rectangle

    /*****************************
     * Draw Outer Frame with Gradient
     *****************************/

    // **1. Draw Bottom Solid Gray Portion of the Frame**
    glColor3fv(FRAME_COLOR); // Set frame color to gray

    glBegin(GL_QUADS);
        // Bottom-left of solid gray
        glVertex2f(-0.5f, -0.5f); // Bottom-left corner

        // Bottom-right of solid gray
        glVertex2f( 0.5f, -0.5f); // Bottom-right corner

        // Top-right of solid gray (start of gradient)
        glVertex2f( 0.5f, GRADIENT_SPLIT_Y); // Top-right of solid gray

        // Top-left of solid gray (start of gradient)
        glVertex2f(-0.5f, GRADIENT_SPLIT_Y); // Top-left of solid gray
    glEnd();

    // **2. Draw Gradient Portion of the Frame**
    glBegin(GL_QUADS);
        // Bottom-left of gradient (same as top-left of solid gray)
        glColor3fv(FRAME_COLOR); // Start with gray at the split point
        glVertex2f(-0.5f, GRADIENT_SPLIT_Y); // Bottom-left of gradient

        // Bottom-right of gradient (same as top-right of solid gray)
        glColor3fv(FRAME_COLOR); // Start with gray at the split point
        glVertex2f( 0.5f, GRADIENT_SPLIT_Y); // Bottom-right of gradient

        // Top-right of gradient
        glColor3fv(GRADIENT_COLOR); // Gradient color at the top
        glVertex2f( 0.5f,  0.5f); // Top-right corner

        // Top-left of gradient
        glColor3fv(GRADIENT_COLOR); // Gradient color at the top
        glVertex2f(-0.5f,  0.5f); // Top-left corner
    glEnd();

    /*****************************
     * Draw Inner Rectangle (Fill) with Texture or Solid Color
     *****************************/

    // **Draw Inner Rectangle (Fill) with Texture**
    if (fillTexture)
    {
        glEnable(GL_TEXTURE_2D);                  // Enable 2D texturing
        glBindTexture(GL_TEXTURE_2D, fillTexture); // Bind the texture

        glColor3f(1.0f, 1.0f, 1.0f); // Set color to white to display the texture's true colors

        glBegin(GL_QUADS);
            // Top-left
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(-0.47f,  0.47f);

            // Bottom-left
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(-0.47f, -0.47f);

            // Bottom-right
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f( 0.47f, -0.47f);

            // Top-right
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f( 0.47f,  0.47f);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
        glDisable(GL_TEXTURE_2D);        // Disable texturing
    }
    else
    {
        // If texture failed to load, fallback to solid fill color
        glColor3fv(FILL_COLOR); // Set fill color
        glBegin(GL_QUADS);
            glVertex2f(-0.47f,  0.47f); // Top-left
            glVertex2f(-0.47f, -0.47f); // Bottom-left
            glVertex2f( 0.47f, -0.47f); // Bottom-right
            glVertex2f( 0.47f,  0.47f); // Top-right
        glEnd();
    }

    /*****************************
     * Draw Gradient Rectangles Underneath Colored Rectangles
     *****************************/

    for (const auto& gr : gradientRectangles)
    {
        // Save the current matrix state
        glPushMatrix();

        // Apply translation
        glTranslatef(gr.translate_x, gr.translate_y, 0.0f);

        // Apply rotation
        glRotatef(gr.rotation_angle, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis

        // Define the properties of the fading rectangle
        float fadeCenterX = 0.0f;   // After transformation, center is at origin
        float fadeCenterY = 0.0f;
        float fadeWidth = 0.07f;     // Width of the fading rectangle
        float fadeHeight = 0.15f;    // Height of the fading rectangle
        bool isHorizontal = gr.isHorizontal;    // Gradient direction

        // Draw the fading rectangle
        drawFadingRectangle(fadeCenterX, fadeCenterY, fadeWidth, fadeHeight, isHorizontal);

        // Restore the previous matrix state
        glPopMatrix();
    }

    /*****************************
     * Draw All Colored Rectangles
     *****************************/
    drawRectangles();

    glPopMatrix(); // Restore the matrix after translating the non-L-functions
    glPushMatrix();
        glTranslatef(.1f, -0.55f, 0.0f);    // Example: No translation
        glRotatef(0.0f, 0.0f, 0.0f, 1.0f); // Rotate 30 degrees around the Z-axis
        glScalef(1.5f, 0.55f, 1.0f);       // Scale down by 20% on X and Y axes
        behind();
    glPopMatrix();

    drawWhite();
   glPushMatrix(); // Save the current matrix
        // Apply uniform transformations
        glTranslatef(-.45f, -0.65f, 0.0f);    // Example: No translation
        glRotatef(0.0f, 0.0f, 0.0f, 1.0f); // Rotate 30 degrees around the Z-axis
        glScalef(0.4f, 0.4f, 1.0f);       // Scale down by 20% on X and Y axes

        // Draw all transformed objects
        Lside();
        Ltop();
        LfrontSeat();
        LdrawSeat();
        LtopRight();
        Lleg2();
        LdrawDarkness();
        Larmrest2();
        LbackSeat();
        Larmrest1();
        Lline();
        LfrontPart();
        Lleg1();
    glPopMatrix(); // Restore the previous matrix

glPushMatrix(); // Save the current matrix
        // Apply uniform transformations
        glTranslatef(.13f, -0.64f, 0.0f);    // Example: No translation
        glRotatef(0.0f, 0.0f, 0.0f, 1.0f); // Rotate 30 degrees around the Z-axis
        glScalef(0.4f, 0.4f, 1.0f);       // Scale down by 20% on X and Y axes

        // Draw all transformed objects
Mside();
MdrawDarkness2();
Marmrest1();
Mtop();
MfrontSeat();
MdrawSeat();
MdrawDarkness();
Marmrest2();
MbackSeat();
MfrontPart();
Mleg2();
Mleg1();
 Mline();
    Mline2();
    Mline3();
    Mline4();

    glPopMatrix(); // Restore the previous matrix
    // Flush and swap buffers
    glFlush();
    glutSwapBuffers();
    glPushMatrix(); // Save the current matrix
        // Apply uniform transformations
        glTranslatef(.66f, -.64f, 0.0f);    // Example: No translation
        glRotatef(0.0f, 0.0f, 0.0f, 1.0f); // Rotate 30 degrees around the Z-axis
        glScalef(0.4f, 0.4f, 1.0f);       // Scale down by 20% on X and Y axes

        // Draw all transformed objects
Rside();
Rtop();
RfrontSeat();  // Draw the rectangle
Rleg1();
RdrawSeat();
Rarmrest1();
RtopLeft();
RbackSeat();
RdrawDarkness();
Rleg2();
Rarmrest2();
RfrontPart();
Rline();
Rline2();


    glPopMatrix(); // Restore the previous matrix
    // Flush and swap buffers
    glFlush();
    glutSwapBuffers();
}



// Reshape callback function to handle window resizing
void reshape(int width, int height)
{
    // Prevent division by zero
    if (height == 0)
        height = 1;

    float aspect = static_cast<float>(width) / static_cast<float>(height);

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width >= height)
    {
        // Width is larger, extend x-axis
        gluOrtho2D(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f);
    }
    else
    {
        // Height is larger, extend y-axis
        gluOrtho2D(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*****************************
 * 7. Main Function
 *****************************/
int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set display mode: Double buffer and RGB color
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Set initial window size
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Set initial window position (optional)
    glutInitWindowPosition(100, 100);

    // Create the window with a title
    glutCreateWindow("Couch Project");

    // Initialize GLEW
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        std::cerr << "GLEW Initialization failed: " << glewGetErrorString(glewStatus) << std::endl;
        return -1;
    }

    // Check OpenGL version
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << version << std::endl;

    // Initialize OpenGL settings and add initial rectangles
    initGL();

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}
