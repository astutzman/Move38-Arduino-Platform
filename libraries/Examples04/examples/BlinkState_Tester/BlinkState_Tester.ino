/*
 * blinkstate tester
 * 
 * An example showing how to use the blinkstate library. 
 * 
 * Each tile has a current locate state. That state maps to a color. 
 * 
 * The tile's state is continously broadcast on all faces. 
 * 
 * Press the button to change the tile's state. The state is 
 * show as a color while the button is held down. 
 * 
 * The "white" state is special. In this state the tile does not broadcast. 
 * 
 * The tile is also always listing on all faces. When it recieves a state from a
 * neighboring tile, it displays the color on the associated face (unless the
 * local button is down, in which case it shows the local state color).
 * 
 */

#include "blinklib.h"
#include "blinkstate.h"

void setup() {
  // put your setup code here, to run once:

  // Show a quick flash on ech face in sequence just to say hi

  FOREACH_FACE(f) {
      setFaceColor( f , BLUE );
      delay(100);
      setFaceColor( f , OFF );
  }
}

Color colors[] = { dim(WHITE,5) , RED, GREEN, BLUE };    // States 0,1,2,3

byte state=0;

void loop() {

  if (buttonPressed()) {            // Rememeber - we get one buttonPressed event each time the button is pressed down

    state++;

    if (state== COUNT_OF( colors )) {   // Wrap back to state 0 (no send) when we get to the end of the color list
      state=0;      
    }

    setColor( colors[ state ] );        // Feedback to user 

    setState( state );                  // Tell the world 


  } else if (!buttonDown()) {             // As long as the button stays down, we will keep showing the new color for user feedback. 

    
    FOREACH_FACE(f) {

      // For each face, show the state recieved from the neighboor on that face
      // (since a face with no neighboor returns state=0 and 0=OFF, faces with no neighboors will be off)

      setFaceColor( f , colors[ getNeighborState(f) ] );


    }

  }
}
