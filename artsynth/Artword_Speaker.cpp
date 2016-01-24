/* Artword_Speaker.cpp
 *
 * Copyright (C) 1992-2011,2016 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Art_Speaker.h"
#include "Artword_Speaker.h"

void Artword_Speaker_draw (Artword artword, Speaker speaker, Graphics g, int numberOfSteps) {
	double oldLineWidth = Graphics_inqLineWidth (g);
	autoArt art = Art_create ();
	for (int i = 0; i <= numberOfSteps; i ++) {
		Artword_intoArt (artword, art.get(), i * artword -> totalTime / numberOfSteps);
		Graphics_setLineWidth (g, 2 + i + i);
		Art_Speaker_draw (art.get(), speaker, g);
	}
	Graphics_setLineWidth (g, oldLineWidth);
}

void Artword_Speaker_movie (Artword artword, Speaker speaker, Graphics graphics) {
	double timeStep = 0.03;
	autoArt art = Art_create ();
	for (double tim = 0.0; tim < artword -> totalTime; tim += timeStep) {
		Artword_intoArt (artword, art.get(), tim);

		Graphics_clearRecording (graphics);
		Graphics_startRecording (graphics);

		Graphics_setViewport (graphics, 0.0, 1.0, 0.0, 1.0);
		Graphics_setColour (graphics, Graphics_WHITE);
		Graphics_setWindow (graphics, 0.0, 1.0, 0.0, 1.0);
		Graphics_fillRectangle (graphics, 0.0, 1.0, 0.0, 1.0);
		Graphics_setColour (graphics, Graphics_BLACK);

		Art_Speaker_draw (art.get(), speaker, graphics);

		Graphics_stopRecording (graphics);

		Graphics_drainWs (graphics);

		Melder_sleep (timeStep);
	}
}

/* End of file Artword_Speaker.cpp */
