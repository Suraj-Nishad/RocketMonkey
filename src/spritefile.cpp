#include "spritefile.h"
#include "sprite.h"
#include <SDL.h>
#include <fstream>
#include <jsoncpp/json/json.h>

void SpriteFile::onLoad(SDL_Renderer* ren, const std::string& sprite_json_path)
{
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    std::ifstream sprite_json_stream;
    sprite_json_stream.open(sprite_json_path, std::ifstream::in);
    if(!sprite_json_stream.is_open()) {
        std::cout  << "Failed to open " << sprite_json_path << "\n";
        return;
    }
    bool parsingSuccessful = reader.parse(sprite_json_stream, root);
    if(!parsingSuccessful) {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration " << sprite_json_path << "\n"
                   << reader.getFormattedErrorMessages();
        return;
    }
    std::string sprite_img = root["sprite"].asString();
    m_texture = IMG_LoadTexture(ren, sprite_img.c_str());
    if(m_texture == NULL) {
        //logSDLError(std::cout, "LoadTexture");
    }
    for(auto iter = root["sub_sprites"].begin(); iter != root["sub_sprites"].end();
        iter++) {
        std::string key = iter.key().asString();
        auto& sprite = *iter;
        SDL_Rect clip;
        clip.x = sprite["x"].asUInt();
        clip.y = sprite["y"].asUInt();
        clip.w = sprite["w"].asUInt();
        clip.h = sprite["h"].asUInt();
        m_sprites[key] =
            new Sprite(*this, key, clip);
    }
    sprite_json_stream.close();
}

