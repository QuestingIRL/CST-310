#include <GL/glut.h>
#include "utilities.h"
//g++ leftCouch.cpp -o left -lGL -lGLU -lglut
// Convert RGBA color values (0-255) to normalized values (0.0f - 1.0f)
/*void convertRGBA(float &colorR, float &colorG, float &colorB, unsigned char R, unsigned char G, unsigned char B, unsigned char A) {
    colorR = R / 255.0f;
    colorG = G / 255.0f;
    colorB = B / 255.0f;
}*/

// Function to draw the solid rectangle with the requested transformations and color
void LfrontSeat() {
    // Define bottom color RGBA values (original solid color)
    unsigned char R_bottom = 192;  // Red component (0-255)
    unsigned char G_bottom = 105;  // Green component (0-255)
    unsigned char B_bottom = 62;   // Blue component (0-255)
    unsigned char A_bottom = 255;  // Alpha component (0-255)

    // Define top color RGBA values (lighter shade for gradient)
    unsigned char R_top = 255;     // Red component (0-255)
    unsigned char G_top = 200;     // Green component (0-255)
    unsigned char B_top = 150;     // Blue component (0-255)
    unsigned char A_top = 255;     // Alpha component (0-255)

    // Convert bottom RGBA to normalized RGB (0.0f - 1.0f)
    float bottomR, bottomG, bottomB;
    convertRGBA(bottomR, bottomG, bottomB, R_bottom, G_bottom, B_bottom, A_bottom);

    // Convert top RGBA to normalized RGB (0.0f - 1.0f)
    float topR, topG, topB;
    convertRGBA(topR, topG, topB, R_top, G_top, B_top, A_top);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: rotation, translation, and scaling
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);    // No rotation applied
    glTranslatef(-0.0f, -0.0f, 0.0f);    // No translation applied
    glScalef(0.5f, 0.5f, 1.0f);          // Scale down the rectangle

    // Begin drawing the gradient rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Top-Left vertex with top color
        glColor3f(topR, topG, topB);     // Set top color
        glVertex2f(-1.0f,  0.2f);        // Top-left vertex

        // Bottom-Left vertex with bottom color
        glColor3f(bottomR, bottomG, bottomB); // Set bottom color
        glVertex2f(-1.0f, -0.2f);        // Bottom-left vertex

        // Bottom-Right vertex with bottom color
        glColor3f(bottomR, bottomG, bottomB); // Set bottom color
        glVertex2f( 0.8f, -0.2f);        // Bottom-right vertex

        // Top-Right vertex with top color
        glColor3f(topR, topG, topB);     // Set top color
        glVertex2f( 0.8f,  0.2f);        // Top-right vertex

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}

void LfrontPart() {
    // Define the base RGBA color (original solid color)
    unsigned char R_base = 49;   // Red component (0-255)
    unsigned char G_base = 58;   // Green component (0-255)
    unsigned char B_base = 67;   // Blue component (0-255)
    unsigned char A_base = 255;  // Alpha component (0-255)

    // Define the gradient RGBA color (lighter shade for gradient)
    unsigned char R_grad = 80;    // Red component (0-255) - Adjusted for lighter shade
    unsigned char G_grad = 100;   // Green component (0-255)
    unsigned char B_grad = 120;   // Blue component (0-255)
    unsigned char A_grad = 255;   // Alpha component (0-255)

    // Convert base RGBA to normalized RGB (0.0f - 1.0f)
    float baseR, baseG, baseB;
    convertRGBA(baseR, baseG, baseB, R_base, G_base, B_base, A_base);

    // Convert gradient RGBA to normalized RGB (0.0f - 1.0f)
    float gradR, gradG, gradB;
    convertRGBA(gradR, gradG, gradB, R_grad, G_grad, B_grad, A_grad);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: rotation, translation, and scaling
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);    // No rotation applied
    glTranslatef(-0.0f, -0.2f, 0.0f);     // Translate the rectangle
    glScalef(0.5f, 0.5f, 1.0f);           // Scale down the rectangle

    // Begin drawing the gradient rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // **Top-Left Vertex**: Gradient color
        glColor3f(gradR, gradG, gradB);     // Set gradient color
        glVertex2f(-1.0f,  0.2f);          // Top-left vertex

        // **Bottom-Left Vertex**: Base color
        glColor3f(baseR, baseG, baseB);     // Set base color
        glVertex2f(-1.0f, -0.2f);          // Bottom-left vertex

        // **Bottom-Right Vertex**: Base color
        glColor3f(baseR, baseG, baseB);     // Set base color
        glVertex2f( 0.8f, -0.2f);          // Bottom-right vertex

        // **Top-Right Vertex**: Gradient color
        glColor3f(gradR, gradG, gradB);     // Set gradient color
        glVertex2f( 0.8f,  0.2f);          // Top-right vertex

    glEnd();  // End of quadrilateral definition

    // Optional: Check for any OpenGL errors during drawing
    // checkOpenGLErrors("frontPart");

    glPopMatrix();  // Restore the previous transformation matrix
}

void LtopLeft() {
    // RGBA color (35, 22, 21, 255)
    unsigned char R = 141;
    unsigned char G = 83;
    unsigned char B = 58;
    unsigned char A = 255;

    // Convert RGBA to normalized RGB values
    float colorR, colorG, colorB;
    convertRGBA(colorR, colorG, colorB, R, G, B, A);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: rotation, translation, and scaling
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);    // Rotate 90 degrees around the Z-axis
    glTranslatef(-0.25f, .92f, 0.0f);    // Translate the rectangle
    glScalef(.45f, 0.9f, 1.0f);            // Scale down the rectangle

    // Begin drawing the solid rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Set the color to the specified RGBA color (normalized)
        glColor3f(colorR, colorG, colorB);

        // Define the four vertices of the rectangle
        glVertex2f(-1.0f,  0.2f); // Top-left vertex
        glVertex2f(-1.0f, -0.2f); // Bottom-left vertex
        glVertex2f( 0.8f, -0.2f); // Bottom-right vertex
        glVertex2f( 0.8f,  0.2f); // Top-right vertex

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}
// Function to draw the solid rectangle with the requested transformations and color
void Lleg1() {
    // RGBA color (35, 22, 21, 255)
    unsigned char R = 39;
    unsigned char G = 45;
    unsigned char B = 56;
    unsigned char A = 255;

    // Convert RGBA to normalized RGB values
    float colorR, colorG, colorB;
    convertRGBA(colorR, colorG, colorB, R, G, B, A);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: rotation, translation, and scaling
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);    // Rotate 90 degrees around the Z-axis
    glTranslatef(0.05f, -.5f, 0.0f);    // Translate the rectangle
    glScalef(.5f, 0.5f, 1.0f);            // Scale down the rectangle

    // Begin drawing the solid rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Set the color to the specified RGBA color (normalized)
        glColor3f(colorR, colorG, colorB);

        // Define the four vertices of the rectangle
        glVertex2f(-1.0f,  0.2f); // Top-left vertex
        glVertex2f(-1.0f, -0.2f); // Bottom-left vertex
        glVertex2f( 0.8f, -0.2f); // Bottom-right vertex
        glVertex2f( 0.8f,  0.2f); // Top-right vertex

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}
void Lleg2() {
    // RGBA color (35, 22, 21, 255)
    unsigned char R = 39;
    unsigned char G = 45;
    unsigned char B = 56;
    unsigned char A = 255;

    // Convert RGBA to normalized RGB values
    float colorR, colorG, colorB;
    convertRGBA(colorR, colorG, colorB, R, G, B, A);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: rotation, translation, and scaling
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);    // Rotate 90 degrees around the Z-axis
    glTranslatef(.05f, .6f, 0.0f);    // Translate the rectangle
    glScalef(.5f, 0.5f, 1.0f);            // Scale down the rectangle

    // Begin drawing the solid rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Set the color to the specified RGBA color (normalized)
        glColor3f(colorR, colorG, colorB);

        // Define the four vertices of the rectangle
        glVertex2f(-1.0f,  0.2f); // Top-left vertex
        glVertex2f(-1.0f, -0.2f); // Bottom-left vertex
        glVertex2f( 0.8f, -0.2f); // Bottom-right vertex
        glVertex2f( 0.8f,  0.2f); // Top-right vertex

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}
void LdrawSeat() {
    // Define the base RGBA color (original solid color)
    unsigned char R_base = 198;  // Red component (0-255)
    unsigned char G_base = 106;  // Green component (0-255)
    unsigned char B_base = 57;   // Blue component (0-255)
    unsigned char A_base = 255;  // Alpha component (0-255)

    // Define the gradient RGBA color (lighter shade for gradient)
    unsigned char R_grad = 244;   // Red component (0-255)
    unsigned char G_grad = 172;   // Green component (0-255)
    unsigned char B_grad = 113;   // Blue component (0-255)
    unsigned char A_grad = 255;   // Alpha component (0-255)

    // Convert base RGBA to normalized RGB (0.0f - 1.0f)
    float baseR, baseG, baseB;
    convertRGBA(baseR, baseG, baseB, R_base, G_base, B_base, A_base);

    // Convert gradient RGBA to normalized RGB (0.0f - 1.0f)
    float gradR, gradG, gradB;
    convertRGBA(gradR, gradG, gradB, R_grad, G_grad, B_grad, A_grad);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: scaling (maintained as in original)
    glScalef(0.5f, 0.5f, 1.0f);  // Scale down the rectangle

    // Begin drawing the seat with gradient
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Top-Left vertex with base color
        glColor3f(baseR, baseG, baseB);  // Set base color
        glVertex2f(-0.55f, 1.0f);         // Top-left

        // Top-Right vertex with base color
        glColor3f(baseR, baseG, baseB);  // Set base color
        glVertex2f( 1.0f, 1.0f);        // Top-right

        // Bottom-Right vertex with gradient color
        glColor3f(gradR, gradG, gradB);  // Set gradient color
        glVertex2f( 0.8f, 0.2f);         // Bottom-right

        // Bottom-Left vertex with gradient color
        glColor3f(gradR, gradG, gradB);  // Set gradient color
        glVertex2f(-1.0f, 0.2f);         // Bottom-left

    glEnd();  // End of quadrilateral definition

    // Optional: Check for any OpenGL errors during drawing
    // checkOpenGLErrors("drawSeat");

    glPopMatrix();  // Restore the previous transformation matrix
}

void Larmrest1() {
    // Define the base RGBA color (original solid color)
    unsigned char R_base = 68;  // Red component (0-255)
    unsigned char G_base = 73;  // Green component (0-255)
    unsigned char B_base = 80;  // Blue component (0-255)
    unsigned char A_base = 255; // Alpha component (0-255)

    // Define the gradient RGBA color (lighter shade for gradient)
    unsigned char R_grad = 100;  // Red component (0-255) - Adjusted for lighter shade
    unsigned char G_grad = 113;  // Green component (0-255)
    unsigned char B_grad = 130;  // Blue component (0-255)
    unsigned char A_grad = 255;  // Alpha component (0-255)

    // Convert base RGBA to normalized RGB (0.0f - 1.0f)
    float baseR, baseG, baseB;
    convertRGBA(baseR, baseG, baseB, R_base, G_base, B_base, A_base);

    // Convert gradient RGBA to normalized RGB (0.0f - 1.0f)
    float gradR, gradG, gradB;
    convertRGBA(gradR, gradG, gradB, R_grad, G_grad, B_grad, A_grad);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: scaling (maintained as in original)
    glScalef(0.5f, 0.5f, 1.0f);            // Scale down the rectangle

    // Begin drawing the armrest with gradient in the opposite direction
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // **Top-Left Vertex**: Base color (swapped)
        glColor3f(baseR, baseG, baseB);     // Set base color
        glVertex2f(1.12f, 1.9f);            // Top-left

        // **Top-Right Vertex**: Base color (swapped)
        glColor3f(baseR, baseG, baseB);     // Set base color
        glVertex2f(1.52f, 1.9f);            // Top-right

        // **Bottom-Right Vertex**: Gradient color (swapped)
        glColor3f(gradR, gradG, gradB);     // Set gradient color
        glVertex2f(1.2f, 0.87f);            // Bottom-right

        // **Bottom-Left Vertex**: Gradient color (swapped)
        glColor3f(gradR, gradG, gradB);     // Set gradient color
        glVertex2f(0.8f, 0.87f);            // Bottom-left

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}


void Larmrest2() {
    // Define the base RGBA color (original solid color)
    unsigned char R_base = 68;  // Red component (0-255)
    unsigned char G_base = 73;  // Green component (0-255)
    unsigned char B_base = 80;  // Blue component (0-255)
    unsigned char A_base = 255; // Alpha component (0-255)

    // Define the gradient RGBA color (lighter shade for gradient)
    unsigned char R_grad = 100;  // Red component (0-255) - Adjusted for lighter shade
    unsigned char G_grad = 113;  // Green component (0-255)
    unsigned char B_grad = 130;  // Blue component (0-255)
    unsigned char A_grad = 255;  // Alpha component (0-255)

    // Convert base RGBA to normalized RGB (0.0f - 1.0f)
    float baseR, baseG, baseB;
    convertRGBA(baseR, baseG, baseB, R_base, G_base, B_base, A_base);

    // Convert gradient RGBA to normalized RGB (0.0f - 1.0f)
    float gradR, gradG, gradB;
    convertRGBA(gradR, gradG, gradB, R_grad, G_grad, B_grad, A_grad);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: scaling and translation (maintained as in original)
    glScalef(0.5f, 0.5f, 1.0f);             // Scale down the rectangle
    glTranslatef(-2.2f, 0.0f, 0.0f);        // Translate the rectangle

    // Begin drawing the armrest with gradient in the opposite direction
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // **Top-Left Vertex**: Base color (swapped)
        glColor3f(baseR, baseG, baseB);     // Set base color
        glVertex2f(1.4f, 1.9f);            // Top-left

        // **Top-Right Vertex**: Base color (swapped)
        glColor3f(baseR, baseG, baseB);     // Set base color
        glVertex2f(1.8f, 1.9f);            // Top-right

        // **Bottom-Right Vertex**: Gradient color (swapped)
        glColor3f(gradR, gradG, gradB);     // Set gradient color
        glVertex2f(1.2f, 0.87f);            // Bottom-right

        // **Bottom-Left Vertex**: Gradient color (swapped)
        glColor3f(gradR, gradG, gradB);     // Set gradient color
        glVertex2f(0.8f, 0.87f);            // Bottom-left

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}


void LbackSeat() {
    // Define the base RGBA color (original solid color)
    unsigned char R_base = 202;  // Red component (0-255)
    unsigned char G_base = 115;  // Green component (0-255)
    unsigned char B_base = 70;   // Blue component (0-255)
    unsigned char A_base = 255;  // Alpha component (0-255)

    // Define the gradient RGBA color (lighter shade for gradient)
    unsigned char R_grad = 244;   // Red component (0-255)
    unsigned char G_grad = 162;   // Green component (0-255)
    unsigned char B_grad = 115;   // Blue component (0-255)
    unsigned char A_grad = 255;   // Alpha component (0-255)

    // Convert base RGBA to normalized RGB (0.0f - 1.0f)
    float baseR, baseG, baseB;
    convertRGBA(baseR, baseG, baseB, R_base, G_base, B_base, A_base);

    // Convert gradient RGBA to normalized RGB (0.0f - 1.0f)
    float gradR, gradG, gradB;
    convertRGBA(gradR, gradG, gradB, R_grad, G_grad, B_grad, A_grad);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: rotation, translation, and scaling
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);     // No rotation applied
    glTranslatef(0.15f, 0.8f, 0.0f);        // Translate the rectangle
    glScalef(0.45f, 1.5f, 1.0f);           // Scale down the rectangle

    // Begin drawing the back seat with gradient
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // **Top-Left Vertex**: Gradient color
        glColor3f(gradR, gradG, gradB);      // Set gradient color
        glVertex2f(-1.0f,  0.2f);           // Top-left vertex

        // **Bottom-Left Vertex**: Base color
        glColor3f(baseR, baseG, baseB);      // Set base color
        glVertex2f(-1.0f, -0.2f);           // Bottom-left vertex

        // **Bottom-Right Vertex**: Base color
        glColor3f(baseR, baseG, baseB);      // Set base color
        glVertex2f( 0.8f, -0.2f);           // Bottom-right vertex

        // **Top-Right Vertex**: Gradient color
        glColor3f(gradR, gradG, gradB);      // Set gradient color
        glVertex2f( 0.8f,  0.2f);           // Top-right vertex

    glEnd();  // End of quadrilateral definition

    // Optional: Check for any OpenGL errors during drawing
    // checkOpenGLErrors("backSeat");

    glPopMatrix();  // Restore the previous transformation matrix
}

void Lside() {
    // RGBA color (35, 22, 21, 255)
    unsigned char R = 34;
    unsigned char G = 23;
    unsigned char B = 19;
    unsigned char A = 255;

    // Convert RGBA to normalized RGB values
    float colorR, colorG, colorB;
    convertRGBA(colorR, colorG, colorB, R, G, B, A);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: rotation, translation, and scaling
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);    // Rotate 90 degrees around the Z-axis
    glTranslatef(-0.35f, .48f, 0.0f);    // Translate the rectangle
    glScalef(.2f, 1.9f, 1.0f);            // Scale down the rectangle

    // Begin drawing the solid rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Set the color to the specified RGBA color (normalized)
        glColor3f(colorR, colorG, colorB);

        // Define the four vertices of the rectangle
        glVertex2f(-1.0f,  0.0f); // Top-left vertex
        glVertex2f(-1.0f, -0.2f); // Bottom-left vertex
        glVertex2f( 0.8f, -0.2f); // Bottom-right vertex
        glVertex2f( 0.8f,  0.3f); // Top-right vertex

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}
void LdrawDarkness() {
    // Define the base color for the rectangle (e.g., dark red)
    unsigned char R = 34;   // Red component (0-255)
    unsigned char G = 23;    // Green component (0-255)
    unsigned char B = 19;    // Blue component (0-255)
    unsigned char A = 255;  // Alpha component (0-255)

    // Convert RGBA to normalized RGB (0.0f - 1.0f)
    float colorR, colorG, colorB;
    convertRGBA(colorR, colorG, colorB, R, G, B, A);

    // Save the current transformation matrix
    glPushMatrix();

    // Apply transformations to position and scale the rectangle
    glTranslatef(-.0f, 0.49f, 0.0f); // Position the rectangle
    glScalef(0.5f, 0.05f, 1.0f);      // Scale to desired size

    // Begin drawing the rectangle
    glBegin(GL_QUADS);
        glColor3f(colorR, colorG, colorB); // Set color once for the entire rectangle
        glVertex2f(-1.0f,  0.2f);        // Top-left vertex

        // Bottom-Left vertex with bottom color
        glVertex2f(-1.0f, -0.2f);        // Bottom-left vertex

        // Bottom-Right vertex with bottom color
        glVertex2f(1.0f, -0.2f);        // Bottom-right vertex

        // Top-Right vertex with top color
        glVertex2f(1.0f,  0.2f);        // Top-right vertex
    glEnd();

    // Check for any OpenGL errors during drawing

    // Restore the previous transformation matrix
    glPopMatrix();
}
void LtopRight() {
    // RGBA color (35, 22, 21, 255)
    unsigned char R = 141;
    unsigned char G = 83;
    unsigned char B = 58;
    unsigned char A = 255;

    // Convert RGBA to normalized RGB values
    float colorR, colorG, colorB;
    convertRGBA(colorR, colorG, colorB, R, G, B, A);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: rotation, translation, and scaling
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);    // Rotate 90 degrees around the Z-axis
    glTranslatef(0.2f, .92f, 0.0f);    // Translate the rectangle
    glScalef(.45f, 0.9f, 1.0f);            // Scale down the rectangle

    // Begin drawing the solid rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Set the color to the specified RGBA color (normalized)
        glColor3f(colorR, colorG, colorB);

        // Define the four vertices of the rectangle
        glVertex2f(-1.0f,  0.2f); // Top-left vertex
        glVertex2f(-1.0f, -0.2f); // Bottom-left vertex
        glVertex2f( 0.8f, -0.2f); // Bottom-right vertex
        glVertex2f( 0.8f,  0.2f); // Top-right vertex

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}
void Ltop() {
    // RGBA color (35, 22, 21, 255)
    unsigned char R = 141;
    unsigned char G = 83;
    unsigned char B = 58;
    unsigned char A = 255;

    // Convert RGBA to normalized RGB values
    float colorR, colorG, colorB;
    convertRGBA(colorR, colorG, colorB, R, G, B, A);

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations: rotation, translation, and scaling
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);    // Rotate 90 degrees around the Z-axis
    glTranslatef(0.2f, .93f, 0.0f);    // Translate the rectangle
    glScalef(.45f, 0.9f, 1.0f);            // Scale down the rectangle

    // Begin drawing the solid rectangle
    glBegin(GL_QUADS);  // Start defining a quadrilateral

        // Set the color to the specified RGBA color (normalized)
        glColor3f(colorR, colorG, colorB);

        // Define the four vertices of the rectangle
        glVertex2f(-1.1f,  0.2f); // Top-left vertex
        glVertex2f(-1.1f, -0.2f); // Bottom-left vertex
        glVertex2f( 0.8f, -0.2f); // Bottom-right vertex
        glVertex2f( 0.8f,  0.2f); // Top-right vertex

    glEnd();  // End of quadrilateral definition

    glPopMatrix();  // Restore the previous transformation matrix
}
void Lline() {
    // Define the RGBA color for the middle line (normalized values)
    float R_middle = 189.0f / 255.0f;   // Red component (0-1.0)
    float G_middle = 101.0f / 255.0f;   // Green component (0-1.0)
    float B_middle = 55.0f / 255.0f;    // Blue component (0-1.0)

    // Define the RGBA color for the side lines (normalized values)
    float R_side = 194.0f / 255.0f;     // Red component (0-1.0)
    float G_side = 107.0f / 255.0f;     // Green component (0-1.0)
    float B_side = 62.0f / 255.0f;      // Blue component (0-1.0)

    glPushMatrix();  // Save the current transformation matrix
    glTranslatef(-0.05f, .0f, 0.0f);    // Translate the rectangle

    // Draw the middle line
    glColor3f(R_middle, G_middle, B_middle);  // Set the color for the middle line
    glLineWidth(1.0f);  // Set the width of the line to 1 pixel

    glBegin(GL_LINES);   // Begin drawing the middle line
        glVertex2f(-0.25f, 0.9f);  // Starting point of the middle line
        glVertex2f(-0.1f, 0.7f);   // Ending point of the middle line
    glEnd();  // End drawing the middle line

    // Draw the left-side line
   // glColor3f(R_side, G_side, B_side);  // Set the color for the side lines

   // glBegin(GL_LINES);   // Begin drawing the left-side line
   //     glVertex2f(-0.26f, 0.9f);  // Slightly to the left of the middle line
   //     glVertex2f(-0.11f, 0.7f);  // Ending point slightly to the left of the middle line
  //  glEnd();  // End drawing the left-side line

    // Draw the right-side line
    glBegin(GL_LINES);   // Begin drawing the right-side line
        glVertex2f(-0.24f, 0.9f);  // Slightly to the right of the middle line
        glVertex2f(-0.09f, 0.7f);  // Ending point slightly to the right of the middle line
    glEnd();  // End drawing the right-side line

    glPopMatrix();  // Restore the previous transformation matrix
}

// GLUT display callback function
/*void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the window
    side();
    top();

   frontSeat();  
   drawSeat();
   topRight();
   leg2();
   drawDarkness();
   armrest2();
   backSeat();

   armrest1();
    line();
   frontPart();
    leg1();
    glFlush();  // Force execution of OpenGL commands
}*/

// Initialize the OpenGL environment
/*void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set the background color to black
    glMatrixMode(GL_PROJECTION);  // Set the projection matrix mode
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);  // Define the orthographic projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode to single-buffered and RGB color
    glutInitWindowSize(500, 500);  // Set window size
    glutInitWindowPosition(100, 100);  // Set window position
    glutCreateWindow("Rotated and Transformed Rectangle");  // Create window with title
    init();  // Call initialization function

    glutDisplayFunc(display);  // Register display callback function
    glutMainLoop();  // Enter the GLUT event-processing loop

    return 0;
}*/
