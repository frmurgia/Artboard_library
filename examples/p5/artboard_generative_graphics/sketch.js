/*
 * Artboard Generative Graphics - p5.js sketch
 *
 * Pattern generativi minimalisti in stile Sol LeWitt
 * controllati da Artboard via Web Serial API
 *
 * Controlli Artboard:
 * - Pot 0: Numero di linee/elementi
 * - Pot 1: Spaziatura/margine
 * - Pot 2: Rotazione
 * - Pot 3: Complessità/variazione
 * - Button 0-3: Cambia pattern (linee, cerchi, griglie, misto)
 * - Touch 0: Rigenera pattern
 */

let port, reader, writer;

// Artboard data
let pot0 = 512, pot1 = 512, pot2 = 512, pot3 = 512;
let currentPattern = 0; // 0-3
let regenerate = false;

// Graphics parameters
let lineCount = 50;
let spacing = 10;
let rotation = 0;
let variation = 0.5;

// Pattern cache
let patternCanvas;

async function setup() {
	createCanvas(windowWidth, windowHeight);

	// Create off-screen graphics for pattern
	patternCanvas = createGraphics(width, height);

	// Initial pattern
	drawPattern();

	noLoop();
	({ port, reader, writer } = await getPort());
	loop();
}

async function draw() {
	background(250);

	// Read serial data from Artboard
	try {
		while (true) {
			const { value, done } = await reader.read();

			if (done) {
				reader.releaseLock();
				break;
			}

			// Parse CSV: pot0,pot1,pot2,pot3,btnPress,touchTrigger
			if (value) {
				let data = value.split(',');
				if (data.length >= 6) {
					pot0 = parseInt(data[0]);
					pot1 = parseInt(data[1]);
					pot2 = parseInt(data[2]);
					pot3 = parseInt(data[3]);
					let btnPress = parseInt(data[4]);
					let touchTrigger = parseInt(data[5]);

					// Update parameters
					updateParameters();

					// Change pattern on button press
					if (btnPress > 0) {
						currentPattern = btnPress - 1; // 0-3
						regenerate = true;
					}

					// Regenerate on touch
					if (touchTrigger > 0) {
						regenerate = true;
					}

					// Redraw if needed
					if (regenerate) {
						drawPattern();
						regenerate = false;
					}
				}
			}
		}
	} catch (e) {
		console.error(e);
	}

	// Display the pattern
	image(patternCanvas, 0, 0);

	// Show current parameters
	displayInfo();
}

function updateParameters() {
	// Map potentiometer values to graphics parameters
	lineCount = map(pot0, 0, 1023, 10, 200);
	spacing = map(pot1, 0, 1023, 2, 50);
	rotation = map(pot2, 0, 1023, 0, TWO_PI);
	variation = map(pot3, 0, 1023, 0, 1);
}

function drawPattern() {
	patternCanvas.clear();
	patternCanvas.background(250);
	patternCanvas.stroke(0);
	patternCanvas.strokeWeight(1);
	patternCanvas.noFill();

	patternCanvas.push();
	patternCanvas.translate(width / 2, height / 2);
	patternCanvas.rotate(rotation);

	// Draw based on current pattern
	switch(currentPattern) {
		case 0:
			drawParallelLines(patternCanvas);
			break;
		case 1:
			drawConcentricCircles(patternCanvas);
			break;
		case 2:
			drawGrid(patternCanvas);
			break;
		case 3:
			drawMixed(patternCanvas);
			break;
	}

	patternCanvas.pop();
}

// Pattern 0: Parallel lines with variation
function drawParallelLines(pg) {
	let w = width * 0.8;
	let h = height * 0.8;

	for (let i = 0; i < lineCount; i++) {
		let x = map(i, 0, lineCount, -w/2, w/2);

		// Add variation
		let offset = random(-spacing * variation, spacing * variation);
		x += offset;

		let y1 = -h/2 + random(-20 * variation, 20 * variation);
		let y2 = h/2 + random(-20 * variation, 20 * variation);

		pg.line(x, y1, x, y2);
	}
}

// Pattern 1: Concentric circles
function drawConcentricCircles(pg) {
	let maxRadius = min(width, height) * 0.4;

	for (let i = 0; i < lineCount; i++) {
		let r = map(i, 0, lineCount, spacing, maxRadius);

		// Add variation
		r += random(-spacing * variation, spacing * variation);

		// Random segments or full circles
		if (random() > 0.5 * variation) {
			pg.ellipse(0, 0, r * 2, r * 2);
		} else {
			let startAngle = random(TWO_PI);
			let endAngle = startAngle + random(PI/4, TWO_PI);
			pg.arc(0, 0, r * 2, r * 2, startAngle, endAngle);
		}
	}
}

// Pattern 2: Grid
function drawGrid(pg) {
	let w = width * 0.8;
	let h = height * 0.8;
	let gridSize = int(sqrt(lineCount));

	let cellW = w / gridSize;
	let cellH = h / gridSize;

	for (let i = 0; i < gridSize; i++) {
		for (let j = 0; j < gridSize; j++) {
			let x = map(i, 0, gridSize, -w/2, w/2);
			let y = map(j, 0, gridSize, -h/2, h/2);

			// Draw different elements based on variation
			let choice = random();
			pg.push();
			pg.translate(x + cellW/2, y + cellH/2);

			if (choice < variation) {
				// Diagonal line
				pg.line(-cellW/2, -cellH/2, cellW/2, cellH/2);
			} else if (choice < variation * 2) {
				// Other diagonal
				pg.line(-cellW/2, cellH/2, cellW/2, -cellH/2);
			} else if (choice < variation * 3) {
				// Circle
				pg.ellipse(0, 0, cellW * 0.8, cellH * 0.8);
			} else {
				// Square
				pg.rect(-cellW * 0.4, -cellH * 0.4, cellW * 0.8, cellH * 0.8);
			}

			pg.pop();
		}
	}
}

// Pattern 3: Mixed - combines elements
function drawMixed(pg) {
	let w = width * 0.8;
	let h = height * 0.8;

	// Random seed for consistent regeneration
	randomSeed(millis() / 1000);

	let structureCount = int(map(variation, 0, 1, 1, 5));

	for (let s = 0; s < structureCount; s++) {
		pg.push();

		let tx = random(-w/4, w/4);
		let ty = random(-h/4, h/4);
		pg.translate(tx, ty);

		let localRotation = random(TWO_PI);
		pg.rotate(localRotation);

		let type = int(random(3));
		let count = int(lineCount / structureCount);

		for (let i = 0; i < count; i++) {
			let pos = map(i, 0, count, -100, 100);

			if (type == 0) {
				// Lines
				pg.line(pos, -100, pos, 100);
			} else if (type == 1) {
				// Circles
				let r = spacing + i * spacing;
				pg.ellipse(0, 0, r, r);
			} else {
				// Arcs
				let r = spacing + i * spacing;
				let start = random(TWO_PI);
				pg.arc(0, 0, r, r, start, start + PI);
			}
		}

		pg.pop();
	}
}

function displayInfo() {
	// Display current pattern and parameters
	fill(0);
	noStroke();
	textAlign(LEFT);
	textSize(14);

	let patternNames = ['Parallel Lines', 'Concentric Circles', 'Grid', 'Mixed'];

	text('Pattern: ' + patternNames[currentPattern], 10, 20);
	text('Lines: ' + int(lineCount), 10, 40);
	text('Spacing: ' + int(spacing), 10, 60);
	text('Rotation: ' + int(degrees(rotation)) + '°', 10, 80);
	text('Variation: ' + (variation * 100).toFixed(0) + '%', 10, 100);

	text('Controls:', 10, height - 100);
	text('Button 1-4: Change pattern', 10, height - 80);
	text('Touch: Regenerate', 10, height - 60);
	text('Pot 0-3: Parameters', 10, height - 40);
	text('Press S to save image', 10, height - 20);
}

function keyPressed() {
	if (key === 's' || key === 'S') {
		// Save image
		let timestamp = year() + '' + month() + '' + day() + '_' + hour() + '' + minute() + '' + second();
		save('artboard_generative_' + timestamp + '.jpg');
	} else if (key === ' ') {
		// Regenerate on spacebar
		drawPattern();
	} else if (key >= '1' && key <= '4') {
		// Change pattern with keys 1-4
		currentPattern = int(key) - 1;
		drawPattern();
	}
}

function windowResized() {
	resizeCanvas(windowWidth, windowHeight);
	patternCanvas = createGraphics(width, height);
	drawPattern();
}
