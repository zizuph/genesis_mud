/*
 * Conduit Chamber of the Elemental Temple of Calia
 * 
 * Created by Jaacar, July 2016
 *
 * Change command from "divine" to "seek" to avoid conflict
 * with new magical item appraise command "divine". Ckrik Jan, 2022
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit TEMPLE_ROOM_BASE;

// Defines
#define SCENARIO_ROOM "/d/Calia/guilds/elementalists/specials/scenario_room"

// Prototypes

// Global Variables
string CONDUIT_POWER = "a dull";
string CONDUIT_FORM = "shade";
string CONDUIT_COLOR = "grey light";
string CONDUIT_FLOW = "sluggishly";
string external_conduit_desc = "a dull shade of grey light";

public void
query_conduit_color_low()
{
    int guild_conduit_score=GUILD_MANAGER->query_guild_conduit();
    switch(guild_conduit_score)
    {
        case 0:
        	CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
        case 1..625:
            CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 626..1250:
            CONDUIT_POWER = "an indistinct";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 1251..1875:
            CONDUIT_POWER = "a vague";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 1876..2500:
            CONDUIT_POWER = "a dappled";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 2501..3125:
            CONDUIT_POWER = "an opaque";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 3126..3750:
            CONDUIT_POWER = "a transclucent";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 3751..4375:
            CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 4376..5000:
            CONDUIT_POWER = "an indistinct";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 5001..5625:
            CONDUIT_POWER = "a vague";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 5626..6250:
            CONDUIT_POWER = "a dappled";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 6251..6875:
            CONDUIT_POWER = "an opaque";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 6876..7500:
            CONDUIT_POWER = "a transclucent";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 7501..8125:
            CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 8126..8750:
            CONDUIT_POWER = "an indistinct";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 8751..9375:
            CONDUIT_POWER = "a vague";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 9376..10000:
            CONDUIT_POWER = "a dappled";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
        case 10001..10625:
            CONDUIT_POWER = "an opaque";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "lazily";
            break;
        case 10626..11250:
            CONDUIT_POWER = "a transclucent";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "lazily";
            break;
        case 11251..11875:
            CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 11876..12500:
            CONDUIT_POWER = "an indistinct";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 12501..13125:
            CONDUIT_POWER = "a vague";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 13126..13750:
            CONDUIT_POWER = "a dappled";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 13751..14375:
            CONDUIT_POWER = "an opaque";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 14376..15000:
            CONDUIT_POWER = "a transclucent";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 15001..15625:
            CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 15626..16250:
            CONDUIT_POWER = "an indistinct";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 16251..16875:
            CONDUIT_POWER = "a vague";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 16876..17500:
            CONDUIT_POWER = "a dappled";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 17501..18125:
            CONDUIT_POWER = "an opaque";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 18126..18750:
            CONDUIT_POWER = "a transclucent";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 18751..19375:
            CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 19376..20000:
            CONDUIT_POWER = "an indistinct";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "lazily";
            break;
        case 20001..20625:
            CONDUIT_POWER = "a vague";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 20626..21250:
            CONDUIT_POWER = "a dappled";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 21251..21875:
            CONDUIT_POWER = "an opaque";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 21876..22500:
            CONDUIT_POWER = "a transclucent";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "pale white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 22501..23125:
            CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 23126..23750:
            CONDUIT_POWER = "an indistinct";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 23751..24375:
            CONDUIT_POWER = "a vague";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 24376..25000:
            CONDUIT_POWER = "a dappled";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 25001..25625:
            CONDUIT_POWER = "an opaque";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 25626..26250:
            CONDUIT_POWER = "a transclucent";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 26251..26875:
            CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 26876..27500:
            CONDUIT_POWER = "an indistinct";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 27501..28125:
            CONDUIT_POWER = "a vague";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 28126..28750:
            CONDUIT_POWER = "a dappled";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 28751..29375:
            CONDUIT_POWER = "an opaque";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 29376..30000:
            CONDUIT_POWER = "a transclucent";
        	CONDUIT_FORM = "hue";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "leisurely";
            break;
        case 30001..30625:
            CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 30626..31250:
            CONDUIT_POWER = "an indistinct";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 31251..31875:
            CONDUIT_POWER = "a vague";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 31876..32500:
            CONDUIT_POWER = "a dappled";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 32501..33125:
            CONDUIT_POWER = "an opaque";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 33126..33750:
            CONDUIT_POWER = "a transclucent";
        	CONDUIT_FORM = "spark";
            CONDUIT_COLOR = "white light";
            CONDUIT_FLOW = "slowly";
            break;
        default:
        	CONDUIT_POWER = "a dull";
        	CONDUIT_FORM = "shade";
            CONDUIT_COLOR = "grey light";
            CONDUIT_FLOW = "sluggishly";
            break;
    }
}

public void
query_conduit_color_mid()
{
    int guild_conduit_score=GUILD_MANAGER->query_guild_conduit();
    switch(guild_conduit_score)
    {
        case 33751..34375:
            CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 34376..35000:
            CONDUIT_POWER = "a shimmering";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 35001..35625:
            CONDUIT_POWER = "a resplendent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 35626..36250:
            CONDUIT_POWER = "a lucent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 36251..36875:
            CONDUIT_POWER = "a glimmering";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 36876..37500:
            CONDUIT_POWER = "an aureate";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 37501..38125:
            CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 38126..38750:
            CONDUIT_POWER = "a shimmering";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 38751..39375:
            CONDUIT_POWER = "a resplendent";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 39376..40000:
            CONDUIT_POWER = "a lucent";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
        case 40001..40625:
            CONDUIT_POWER = "a glimmering";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 40626..41250:
            CONDUIT_POWER = "an aureate";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 41251..41875:
            CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 41876..42500:
            CONDUIT_POWER = "a shimmering";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 42501..43125:
            CONDUIT_POWER = "a resplendent";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 43126..43750:
            CONDUIT_POWER = "a lucent";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 43751..44375:
            CONDUIT_POWER = "a glimmering";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 44376..45000:
            CONDUIT_POWER = "an aureate";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 45001..45625:
            CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 45626..46250:
            CONDUIT_POWER = "a shimmering";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 46251..46875:
            CONDUIT_POWER = "a resplendent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 46876..47500:
            CONDUIT_POWER = "a lucent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 47501..48125:
            CONDUIT_POWER = "a glimmering";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 48126..48750:
            CONDUIT_POWER = "an aureate";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 48751..49375:
            CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 49376..50000:
            CONDUIT_POWER = "a shimmering";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "deliberately";
            break;
        case 50001..50625:
            CONDUIT_POWER = "a resplendent";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 50626..51250:
            CONDUIT_POWER = "a lucent";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 51251..51875:
            CONDUIT_POWER = "a glimmering";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 51876..52500:
            CONDUIT_POWER = "an aureate";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 52501..53125:
            CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 53126..53750:
            CONDUIT_POWER = "a shimmering";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 53751..54375:
            CONDUIT_POWER = "a resplendent";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 54376..55000:
            CONDUIT_POWER = "a lucent";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 55001..55625:
            CONDUIT_POWER = "a glimmering";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 55626..56250:
            CONDUIT_POWER = "an aureate";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "silvery white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 56251..56875:
            CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 56876..57500:
            CONDUIT_POWER = "a shimmering";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 57501..58125:
            CONDUIT_POWER = "a resplendent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 58126..58750:
            CONDUIT_POWER = "a lucent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 58751..59375:
            CONDUIT_POWER = "a glimmering";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 59376..60000:
            CONDUIT_POWER = "an aureate";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "enthusiastically";
            break;
        case 60001..60625:
            CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 60626..61250:
            CONDUIT_POWER = "a shimmering";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 61251..61875:
            CONDUIT_POWER = "a resplendent";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 61876..62500:
            CONDUIT_POWER = "a lucent";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 62501..63125:
            CONDUIT_POWER = "a glimmering";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 63126..63750:
            CONDUIT_POWER = "an aureate";
        	CONDUIT_FORM = "opulence";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 63751..64375:
            CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 64376..65000:
            CONDUIT_POWER = "a shimmering";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 65001..65625:
            CONDUIT_POWER = "a resplendent";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 65626..66250:
            CONDUIT_POWER = "a lucent";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 66251..66875:
            CONDUIT_POWER = "a glimmering";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        case 66876..67500:
            CONDUIT_POWER = "an aureate";
        	CONDUIT_FORM = "chroma";
            CONDUIT_COLOR = "pure white light";
            CONDUIT_FLOW = "quickly";
            break;
        default:
        	CONDUIT_POWER = "an incandescent";
        	CONDUIT_FORM = "glow";
            CONDUIT_COLOR = "clear white light";
            CONDUIT_FLOW = "slowly";
            break;
    }
}

public void
query_conduit_color_high()
{
    int guild_conduit_score=GUILD_MANAGER->query_guild_conduit();
    switch(guild_conduit_score)
    {
        case 67501..68125:
            CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "quickly";
            break;
        case 68126..68750:
            CONDUIT_POWER = "a scintilating";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "quickly";
            break;
        case 68751..69375:
            CONDUIT_POWER = "a coruscating";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "quickly";
            break;
        case 69376..70000:
            CONDUIT_POWER = "a luminous";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "quickly";
            break;
        case 70001..70625:
            CONDUIT_POWER = "a prismatic";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 70626..71250:
            CONDUIT_POWER = "a blinding";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 71251..71875:
            CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 71876..72500:
            CONDUIT_POWER = "a scintilating";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 72501..73125:
            CONDUIT_POWER = "a coruscating";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 73126..73750:
            CONDUIT_POWER = "a luminous";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 73751..74375:
            CONDUIT_POWER = "a prismatic";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 74376..75000:
            CONDUIT_POWER = "a blinding";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 75001..75625:
            CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 75626..76250:
            CONDUIT_POWER = "a scintilating";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 76251..76875:
            CONDUIT_POWER = "a coruscating";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 76876..77500:
            CONDUIT_POWER = "a luminous";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 77501..78125:
            CONDUIT_POWER = "a prismatic";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 78126..78750:
            CONDUIT_POWER = "a blinding";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 78751..79375:
            CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 79376..80000:
            CONDUIT_POWER = "a scintilating";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "rapidly";
            break;
        case 80001..80625:
            CONDUIT_POWER = "a coruscating";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 80626..81250:
            CONDUIT_POWER = "a luminous";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 81251..81875:
            CONDUIT_POWER = "a prismatic";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 81876..82500:
            CONDUIT_POWER = "a blinding";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 82501..83125:
            CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 83126..83750:
            CONDUIT_POWER = "a scintilating";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 83751..84375:
            CONDUIT_POWER = "a coruscating";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 84376..85000:
            CONDUIT_POWER = "a luminous";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 85001..85625:
            CONDUIT_POWER = "a prismatic";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 85626..86250:
            CONDUIT_POWER = "a blinding";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 86251..86875:
            CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 86876..87500:
            CONDUIT_POWER = "a scintilating";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 87501..88125:
            CONDUIT_POWER = "a coruscating";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 88126..88750:
            CONDUIT_POWER = "a luminous";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 88751..89375:
            CONDUIT_POWER = "a prismatic";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 89376..90000:
            CONDUIT_POWER = "a blinding";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "silvery brightness";
            CONDUIT_FLOW = "hastily";
            break;
        case 90001..90625:
            CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 90626..91250:
            CONDUIT_POWER = "a scintilating";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 91251..91875:
            CONDUIT_POWER = "a coruscating";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 91876..92500:
            CONDUIT_POWER = "a luminous";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 92501..93125:
            CONDUIT_POWER = "a prismatic";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 93126..93750:
            CONDUIT_POWER = "a blinding";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 93751..94375:
            CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 94376..95000:
            CONDUIT_POWER = "a scintilating";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 95001..95625:
            CONDUIT_POWER = "a coruscating";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 95626..96250:
            CONDUIT_POWER = "a luminous";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 96251..96875:
            CONDUIT_POWER = "a prismatic";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 96876..97500:
            CONDUIT_POWER = "a blinding";
        	CONDUIT_FORM = "cascade";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 97501..98125:
            CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 98126..98750:
            CONDUIT_POWER = "a scintilating";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 98751..99375:
            CONDUIT_POWER = "a coruscating";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 99376..100000:
            CONDUIT_POWER = "a luminous";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 100001..100625:
            CONDUIT_POWER = "a prismatic";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        case 100626..101250:
            CONDUIT_POWER = "a blinding";
        	CONDUIT_FORM = "radiance";
            CONDUIT_COLOR = "pure brightness";
            CONDUIT_FLOW = "swiftly";
            break;
        default:
        	CONDUIT_POWER = "a glittering";
        	CONDUIT_FORM = "illumination";
            CONDUIT_COLOR = "brightness";
            CONDUIT_FLOW = "quickly";
            break;
    }
}            

public string
conduit_desc()
{
    string conduit_desc;
    int guild_conduit_score;
    
    guild_conduit_score = GUILD_MANAGER->query_guild_conduit();
    
    if (guild_conduit_score == 0)
    {
    	conduit_desc = "This large cylindrical tube known only as the "+
	        "conduit appears to stretch from inside the floor and "+
	        "goes right up into the ceiling. It is made from some sort "+
	        "of clear material like glass. Inside of the tube you see "+
	        "blackness. A hollow feeling passes through you. You somehow "+
	        "sense that this is the energy source that is powering the "+
	        "entire temple and right now, it is empty.\n";
    }
    
    else
    {
    	switch(guild_conduit_score)
    	{
    		case 0:
    			break;
    		case 1..33750:
    			TO->query_conduit_color_low();
    			break;
    		case 33751..67500:
    			TO->query_conduit_color_mid();
    			break;
    		case 67501..101250:
    			TO->query_conduit_color_high();
    			break;
    		default:
    			CONDUIT_POWER = "a dull";
	        	CONDUIT_FORM = "shade";
	            CONDUIT_COLOR = "grey light";
	            CONDUIT_FLOW = "sluggishly";
	            break;
	    }
    		
	    conduit_desc = "This large cylindrical tube known only as the "+
	        "conduit appears to stretch from inside the floor and "+
	        "goes right up into the ceiling. It is made from some sort "+
	        "of clear material like glass yet it is flexible as you see "+
	        "it pulsing inwards and outwards, almost like a heartbeat. "+
	        "Inside of the tube you see "+CONDUIT_POWER+" " +
	        CONDUIT_FORM+" of "+CONDUIT_COLOR+" that "+
	        "seems to be "+CONDUIT_FLOW+" flowing its way up into the ceiling. "+
	        "You somehow sense that this is the energy source that is "+
	        "powering the entire temple.\n";
	}
    
    external_conduit_desc = CONDUIT_POWER + " " + CONDUIT_FORM + " of " + CONDUIT_COLOR;
    return conduit_desc;
}

public void
create_temple_room()
{
    set_short("Conduit Chamber");
    set_long("This chamber is unlike anything you have ever seen "+
        "anywhere in all of the realms. In the centre of the room "+
        "you see a large cylindrical tube leading from the floor "+
        "up into the ceiling. All four walls, the ceiling and the "+
        "floor are made of a smoothly polished grey stone. The main "+
        "hallway lies back out to the north.\n\n");   
                   
    add_exit(ELEMENTALIST_TEMPLE + "hall3", "north");     
    
    try_item(({"floor","roof","ceiling","wall","walls"}),"The walls, "+
        "floor and ceiling are all constructed with a grey stone and "+
        "then smoothed and polished afterwards. The floor is quite "+
        "comfortable to walk on.\n");
    
    add_item(({"tube","cylindrical tube","large tube",
        "large cylindrical tube","conduit"}),VBFC_ME("conduit_desc"));

}

public int
do_divine(string str)
{
	int scenario_number = 0;
	string name = TP->query_real_name();
	
	// If they aren't a Master Cleric (or higher) then don't do anything
	if (!GUILD_MANAGER->query_is_master_cleric(name))
	{
		if (!GUILD_MANAGER->query_is_full_master(name))
		{
			if (!GUILD_MANAGER->query_is_elder_cleric(name))
			{
				NF("What?\n");
				return 0;
			}
		}
	}
	
	// Is scenario room busy? If so, tell them to try again later
	if (SCENARIO_ROOM->query_occupied() == 1)
	{
		TP->catch_msg("You hear a voice echo in your mind saying, 'Someone "+
		    "else is currently divining at the moment. Please try again in "+
		    "a few minutes.\n");
		return 1;
	}
	
	// Player hasn't done any scenarios, they need Fire 
	if (!GUILD_MANAGER->query_has_completed_scenarios(name))
	{
		TP->catch_msg("A voice echoes through your mind saying, 'Welcome! "+
		    "My name is Nysa. I will be your guide on this journey you are "+
		    "about to take.\n\n"); 
		TP->move_living("X",SCENARIO_ROOM,1,0);
		SCENARIO_ROOM->start_scenario("fire",TP);
		return 1;
	}
	
	// Player has already completed all scenarios but wants to do them again
	if (GUILD_MANAGER->query_has_completed_scenarios(name) == 5)
	{
		if (!str)
		{
			NF("Seek which? Fire, Earth, Air, Water or Spirit?\n");
			return 0;
		}
		
		switch(lower_case(str))
		{
			case "fire":
				SCENARIO_ROOM->set_occupied(1);
				TP->move_living("X",SCENARIO_ROOM,1,0);
				SCENARIO_ROOM->start_scenario("fire",TP);
				break;
			case "earth":
				SCENARIO_ROOM->set_occupied(1);
				TP->move_living("X",SCENARIO_ROOM,1,0);
				SCENARIO_ROOM->start_scenario("earth",TP);
				break;
			case "air":
				SCENARIO_ROOM->set_occupied(1);
				TP->move_living("X",SCENARIO_ROOM,1,0);
				SCENARIO_ROOM->start_scenario("air",TP);
				break;
			case "water":
				SCENARIO_ROOM->set_occupied(1);
				TP->move_living("X",SCENARIO_ROOM,1,0);
				SCENARIO_ROOM->start_scenario("water",TP);
				break;
			case "spirit":
				SCENARIO_ROOM->set_occupied(1);
				TP->move_living("X",SCENARIO_ROOM,1,0);
				SCENARIO_ROOM->start_scenario("life",TP);
				break;
			default:
				NF("Seek which? Fire, Earth, Air, Water or Spirit?\n");
				return 0;
				break;
		}
		
		tell_room(TO,QCTNAME(TP) + " suddenly disappears!\n");
		return 1;
	}
	
	// Player has done at least one of the scenarios before and needs to
	// go to the next one.
	
	scenario_number = GUILD_MANAGER->query_has_completed_scenarios(name);
	
	switch(scenario_number)
	{
		case 1: // Done Fire, needs Earth
			SCENARIO_ROOM->set_occupied(1);
			TP->move_living("X",SCENARIO_ROOM,1,0);
			SCENARIO_ROOM->start_scenario("earth",TP);
			break;
		case 2: // Done Fire and Earth, needs Air
			SCENARIO_ROOM->set_occupied(1);
			TP->move_living("X",SCENARIO_ROOM,1,0);
			SCENARIO_ROOM->start_scenario("air",TP);
			break;
		case 3: // Done Fire, Earth and Air, needs Water
			SCENARIO_ROOM->set_occupied(1);
			TP->move_living("X",SCENARIO_ROOM,1,0);
			SCENARIO_ROOM->start_scenario("water",TP);
			break;
		case 4: // Done Fire, Earth, Air and Water, needs Life
			SCENARIO_ROOM->set_occupied(1);
			TP->move_living("X",SCENARIO_ROOM,1,0);
			SCENARIO_ROOM->start_scenario("life",TP);
			break;
	}
	
	tell_room(TO,QCTNAME(TP) + " suddenly disappears!\n");	
	return 1;
}

public string
query_external_conduit_desc()
{
    return external_conduit_desc;
}

void
init()
{
    ::init();
    // Ckrik 1/21/2022 "divine" conflicts with new "divine" appraise
    // command. Change to "seek" to avoid conflict.

    //add_action(do_divine,"divine");
    add_action(do_divine,"seek");
}
