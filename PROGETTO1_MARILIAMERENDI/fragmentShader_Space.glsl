#version 330 core

out vec4 fragColor;
in vec2 fragCoord;  // Screen space coordinate (in pixels)
uniform int iFrame;  // The frame count, used to move stars
uniform int height;


// Return random noise in the range [0.0, 1.0], based on a 2D input.
float Noise2d(in vec2 x)
{
    // Simple hash-based noise function
    float xhash = cos(x.x * 37.0);
    float yhash = cos(x.y * 57.0);
    return fract(415.92653 * (xhash + yhash));  // Generate random noise
}

// Generate a starfield based on noise and a threshold for visibility
float StarField(in vec2 vSamplePos, float threshold)
{
    float starVal = Noise2d(vSamplePos);
    if (starVal >= threshold)
    {
        // Apply a sharp cut-off to make stars visible only above a certain threshold
        starVal = pow((starVal - threshold) / (1.0 - threshold), 10.0);  // Sharpen the stars' visibility
    }
    else
    {
        starVal = 0.0;  // No star below threshold
    }
    return starVal;
}

void main()
{
    // Set a background color, fading from dark blue at the top to black at the bottom
    vec3 backgroundColor = vec3(0.0, 0.0, 0.1) * fragCoord.y / height;
    
    // Define the threshold for star visibility (lower = more stars)
    float threshold = 0.95;  // Adjust this to control star density

    // Control the speed of star movement
    float speed = 0.0005;  // How fast the stars move (higher = faster)
    
    // Calculate the position of the stars by adding frame-based movement
    vec2 samplePos = fragCoord.xy + vec2(speed * float(iFrame), 0.0);
    
    // Generate the starfield at the sample position
    float starValue = StarField(samplePos, threshold);
    
    // Add the stars to the background color
    vec3 starColor = vec3(1.0) * starValue;  // Stars are white
    
    // Combine the star color with the background
    vec3 finalColor = backgroundColor + starColor;
    
    // Output the final color
    fragColor = vec4(finalColor, 1.0);
}
