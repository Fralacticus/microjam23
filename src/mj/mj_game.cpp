#include "mj/mj_game.h"

#include "bn_music.h"

#include "bn_music_items.h"

namespace mj
{

int game::recommended_total_frames(int base_total_frames, int completed_games, const game_data& data)
{
    bn::fixed tempo = recommended_music_tempo(completed_games, data);
    int total_frames = (base_total_frames / tempo).right_shift_integer();
    BN_ASSERT(total_frames >= minimum_frames && total_frames <= maximum_frames,
              "Invalid base total frames: ", base_total_frames, " - ", tempo, " - ", total_frames);

    return total_frames;
}

bn::fixed game::recommended_music_tempo(int completed_games, [[maybe_unused]] const game_data& data)
{
    constexpr bn::fixed minimum_tempo = 1.15;
    constexpr bn::fixed maximum_tempo = 1.85;
    constexpr bn::fixed tempo_diff = maximum_tempo - minimum_tempo;
    constexpr int minimum_games = 0;
    constexpr int maximum_games = 45;

    completed_games = bn::clamp(completed_games, minimum_games, maximum_games);
    return minimum_tempo + ((completed_games * tempo_diff) / maximum_games);
}

void game::play_music(bn::music_item music_item, int completed_games, const game_data& data)
{
    bn::music::play(music_item, 1, false);
    bn::music::set_tempo(recommended_music_tempo(completed_games, data));
}

int game::play_jingle(game_jingle_type jingle, int completed_games, const game_data& data)
{
    bn::fixed base_seconds = 8;

    switch(jingle)
    {

    case game_jingle_type::EXELOTL01:
        play_music(bn::music_items::mj_exelotl01, completed_games, data);
        base_seconds = 6;
        break;

    case game_jingle_type::EXELOTL02A:
        play_music(bn::music_items::mj_exelotl02a, completed_games, data);
        break;

    case game_jingle_type::EXELOTL02B:
        play_music(bn::music_items::mj_exelotl02b, completed_games, data);
        base_seconds = 9;
        break;

    case game_jingle_type::TOTSNUK01:
        play_music(bn::music_items::mj_totsnuk01, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK02:
        play_music(bn::music_items::mj_totsnuk02, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK03:
        play_music(bn::music_items::mj_totsnuk03, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK04A:
        play_music(bn::music_items::mj_totsnuk04a, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK04B:
        play_music(bn::music_items::mj_totsnuk04b, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK05:
        play_music(bn::music_items::mj_totsnuk05, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK06:
        play_music(bn::music_items::mj_totsnuk06, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK07:
        play_music(bn::music_items::mj_totsnuk07, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK10:
        play_music(bn::music_items::mj_totsnuk10, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK11:
        play_music(bn::music_items::mj_totsnuk11, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK12A:
        play_music(bn::music_items::mj_totsnuk12a, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK12B:
        play_music(bn::music_items::mj_totsnuk12b, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK13:
        play_music(bn::music_items::mj_totsnuk13, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK14:
        play_music(bn::music_items::mj_totsnuk14, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK15:
        play_music(bn::music_items::mj_totsnuk15, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK16:
        play_music(bn::music_items::mj_totsnuk16, completed_games, data);
        break;

    case game_jingle_type::TOTSNUK17:
        play_music(bn::music_items::mj_totsnuk17, completed_games, data);
        break;

    default:
        BN_ERROR("Unknown jingle: ", int(jingle));
        break;
    }

    int base_total_frames = (base_seconds * 60).right_shift_integer() - 24 - 24;
    return recommended_total_frames(base_total_frames, completed_games, data);
}

void game::credits([[maybe_unused]] credits_type type, [[maybe_unused]] bn::ivector<bn::string_view>& output) const
{
}

}