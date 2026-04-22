#include "Nukoli.h"

uint8_t frameBuffer[SIZE] = {};
Color palette[16];
Font defaultFont;
const std::string assetsFolder = "assets/";

void populatePalette() {
    palette[0] = { 221, 207, 153 }; // #ddcf99
    palette[1] = { 204, 168, 123 }; // #cca87b
    palette[2] = { 185, 122,  96 }; // #b97a60
    palette[3] = { 156,  82,  78 }; // #9c524e
    palette[4] = { 119,  66,  81 }; // #774251
    palette[5] = { 75,  61,  68 }; // #4b3d44
    palette[6] = { 78,  84,  99 }; // #4e5463
    palette[7] = { 91, 125, 115 }; // #5b7d73
    palette[8] = { 142, 159, 125 }; // #8e9f7d
    palette[9] = { 100,  83,  85 }; // #645355
    palette[10] = { 140, 124, 121 }; // #8c7c79
    palette[11] = { 169, 156, 141 }; // #a99c8d
    palette[12] = { 125, 123,  98 }; // #7d7b62
    palette[13] = { 170, 162,  93 }; // #aaa25d
    palette[14] = { 132, 109,  89 }; // #846d59
    palette[15] = { 168, 138,  94 }; // #a88a5e
}

void init() {
	
	populatePalette();
    defaultFont.loadFromFile("defaultFont.nf");
	std::fill(std::begin(frameBuffer), std::end(frameBuffer), t);
}


void CreateScreenTexture(sf::Texture& screenTexture, Color palette[16]) {
	std::vector<uint8_t> pixels(WIDTH * HEIGHT * 4);
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		uint8_t index = frameBuffer[i];
		if (index == t) {
			pixels[i * 4 + 0] = 0;
			pixels[i * 4 + 1] = 0;
			pixels[i * 4 + 2] = 0;
			pixels[i * 4 + 3] = 0; // alpha
		}
		else {
			Color c = palette[index];

			pixels[i * 4 + 0] = c.r;
			pixels[i * 4 + 1] = c.g;
			pixels[i * 4 + 2] = c.b;
			pixels[i * 4 + 3] = 255; // alpha
		}
		
	}
	screenTexture.update(pixels.data());
}


void run(Game& game) {
    init();
    game.Start();
    sf::RenderWindow window(sf::VideoMode({ 1024, 1024 }), game.gameName);
    sf::Texture screen(sf::Vector2u(WIDTH, HEIGHT));
    sf::Clock clock;
    const float timestep = 1.f / 60.f;

    auto makeLetterboxView = [&]() -> sf::View {
        sf::Vector2u winSize = window.getSize();
        float winW = static_cast<float>(winSize.x);
        float winH = static_cast<float>(winSize.y);

        float size = std::min(winW, winH); 
        float left = (winW - size) / 2.f / winW;
        float top = (winH - size) / 2.f / winH;
        float width = size / winW;
        float height = size / winH;

        sf::View view(sf::FloatRect({ 0.f, 0.f }, { (float)WIDTH, (float)HEIGHT }));
        view.setViewport(sf::FloatRect({ left, top }, { width, height }));
        return view;
        };

    sf::View gameView = makeLetterboxView();

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

           
            if (event->is<sf::Event::Resized>())
                gameView = makeLetterboxView();
        }

        static float accumulator = 0;
        accumulator += dt;
        while (accumulator >= timestep)
        {
            //ClearFrameBuffer();
            UpdateAllTimers();
            game.Update();
            accumulator -= timestep;
        }

        window.clear(sf::Color::Black); 
        window.setView(gameView);

        game.Draw();
        CreateScreenTexture(screen, palette);
        sf::Sprite screenSprite(screen);
        screenSprite.setScale({ (float)WIDTH / WIDTH, (float)HEIGHT / HEIGHT }); 
        window.draw(screenSprite);

        window.display();
    }
}

