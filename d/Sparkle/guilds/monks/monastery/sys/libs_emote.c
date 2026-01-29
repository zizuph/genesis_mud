/*******************************************************************\
| LIBS_EMOTE.C                                                      |
+-------------------------------------------------------------------+
| Library functions to classify emotes.                             |
\*******************************************************************/

/*
 * 10/10/08 Lavellan    Starting to add new emotes, at bottom of list
 * 07/06/18 Arandir     Emote and adverb list extended
 * 04/08/26 Arandir     Mild emote and adverb list extension
 *                      Improved logging of unknown emote sources
 * 04/08/25 Arandir     Created
 *
 */

#include <macros.h>
#include <cmdparse.h>

#include "../defs.h"

inherit M_LOGGING_LIBS;

//-------------------------------------------------------------------

/*******************************************************************\
| Emote classification functions                                    |
\*******************************************************************/


/*
 * Function name : m_get_emote_soul
 * Description   : Locates a soul implementing an emote.
 *
 */

object m_get_emote_soul (object oActor, string sEmote)
{
  string  *asSouls;
  object  oSoul;
  int     iSoul;
  mapping mCommands;

  asSouls = oActor->query_cmdsoul_list ();
  for (iSoul = 0 ; iSoul < sizeof (asSouls) ; iSoul ++)
  {
    // We do not fix uid and euid for it is not possible
    // that any of the souls would not be loaded before.
    oSoul = find_object (asSouls [iSoul]);
    mCommands = oSoul->query_cmdlist ();
    if (member_array (sEmote, m_indices (mCommands)) >= 0) return (oSoul);
  }

  return (NULL);
}


/*
 * Function name : m_classify_emote
 * Description   : Classifies an emote and adverb pair.
 *
 */

int m_classify_emote (object oActor, string sEmote, string sAdverb, int iAttributes)
{
  // The following lists are done as local variables in an attempt
  // to reduce the size of instances that inherit this library.
  //
  // Similarly, the following lists are done as mappings in an
  // attempt to reduce the lookup time.
  //
  // Not sure if either helps anything though :-) ...

  mapping miEmotes = ([

    "ack"                 : M_EMOTE_NEUTRAL,
    "admire"              : M_EMOTE_ADMIRATION | M_EMOTE_EXTREME,
    "agfarewell"          : M_EMOTE_POLITENESS,
    "agree"               : M_EMOTE_ADMIRATION,
    "apologize"           : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,
    "applaud"             : M_EMOTE_ADMIRATION | M_EMOTE_EXTREME,
    "avert"               : M_EMOTE_NEUTRAL,

    "back"                : M_EMOTE_NEUTRAL,
    "bat"                 : M_EMOTE_FONDNESS,
    "beam"                : M_EMOTE_FRIENDSHIP,
    "bearhug"             : M_EMOTE_FRIENDSHIP,
    "beckon"              : M_EMOTE_FONDNESS,
    "beg"                 : M_EMOTE_DEBASEMENT | M_EMOTE_EXTREME,
    "bite"                : M_EMOTE_FONDNESS | M_EMOTE_MILD,
    "blanch"              : M_EMOTE_HOSTILITY,
    "blank"               : M_EMOTE_NEUTRAL,
    "blink"               : M_EMOTE_NEUTRAL,
    "blow"                : M_EMOTE_FONDNESS,
    "blush"               : M_EMOTE_FONDNESS | M_EMOTE_MILD,
    "boggle"              : M_EMOTE_NEUTRAL,
    "bounce"              : M_EMOTE_FRIENDSHIP,
    "bow"                 : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,
    "brighten"            : M_EMOTE_NEUTRAL,
    "burp"                : M_EMOTE_HOSTILITY,

    "cackle"              : M_EMOTE_NEUTRAL,
    "caress"              : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "cast"                : M_EMOTE_NEUTRAL,
    "cheer"               : M_EMOTE_ADMIRATION,
    "choke"               : M_EMOTE_NEUTRAL,
    "chortle"             : M_EMOTE_NEUTRAL,
    "chuckle"             : M_EMOTE_FRIENDSHIP | M_EMOTE_MILD,
    "clap"                : M_EMOTE_ADMIRATION,
    "clear"               : M_EMOTE_POLITENESS | M_EMOTE_MILD,
    "comfort"             : M_EMOTE_FRIENDSHIP,
    "complain"            : M_EMOTE_FRIENDSHIP,
    "compliment"          : M_EMOTE_ADMIRATION | M_EMOTE_EXTREME,
    "conf"                : M_EMOTE_NEUTRAL,
    "confuse"             : M_EMOTE_NEUTRAL,
    "confused"            : M_EMOTE_NEUTRAL,
    "congrat"             : M_EMOTE_ADMIRATION | M_EMOTE_EXTREME,
    "congratulate"        : M_EMOTE_ADMIRATION | M_EMOTE_EXTREME,
    "cough"               : M_EMOTE_NEUTRAL,
    "cower"               : M_EMOTE_DEBASEMENT,
    "cprot"               : M_EMOTE_FRIENDSHIP,
    "cringe"              : M_EMOTE_DEBASEMENT,
    "cross"               : M_EMOTE_POLITENESS | M_EMOTE_MILD,
    "cry"                 : M_EMOTE_NEUTRAL,
    "cuddle"              : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "curl"                : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "curse"               : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "curtsey"             : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,

    "dance"               : M_EMOTE_FONDNESS,
    "dcheck"              : M_EMOTE_NEUTRAL,
    "dconvince"           : M_EMOTE_NEUTRAL,
    "despair"             : M_EMOTE_NEUTRAL,
    "dfare"               : M_EMOTE_POLITENESS,
    "dgift"               : M_EMOTE_FRIENDSHIP | M_EMOTE_EXTREME,
    "disagree"            : M_EMOTE_DISAGREEMENT,
    "drool"               : M_EMOTE_NEUTRAL,
    "dsalute"             : M_EMOTE_POLITENESS,
    "dsmi"                : M_EMOTE_FRIENDSHIP,
    "duh"                 : M_EMOTE_NEUTRAL,

    "ectios"              : M_EMOTE_POLITENESS,
    "eeks"                : M_EMOTE_NEUTRAL,
    "esp"                 : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "eth"                 : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "excuse"              : M_EMOTE_POLITENESS,
    "explode"             : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "eyebrow"             : M_EMOTE_NEUTRAL,
    "eyelook"             : M_EMOTE_NEUTRAL,
    "eyepeer"             : M_EMOTE_NEUTRAL,
    "eyepoke"             : M_EMOTE_NEUTRAL,
    "eyeshut"             : M_EMOTE_NEUTRAL,
    "eyetwi"              : M_EMOTE_NEUTRAL,
    "eyetwinkle"          : M_EMOTE_NEUTRAL,
    "eyewink"             : M_EMOTE_FONDNESS | M_EMOTE_MILD,

    "fart"                : M_EMOTE_HOSTILITY,
    "fawn"                : M_EMOTE_DEBASEMENT,
    "feign"               : M_EMOTE_NEUTRAL,
    "ffinger"             : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "fidget"              : M_EMOTE_NEUTRAL,
    "fint"                : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "flean"               : M_EMOTE_NEUTRAL,
    "flex"                : M_EMOTE_NEUTRAL,
    "flip"                : M_EMOTE_NEUTRAL,
    "flirt"               : M_EMOTE_FONDNESS,
    "fondle"              : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "forgive"             : M_EMOTE_FRIENDSHIP,
    "french"              : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "fret"                : M_EMOTE_NEUTRAL,
    "frown"               : M_EMOTE_DISAGREEMENT | M_EMOTE_MILD,
    "fume"                : M_EMOTE_DISAGREEMENT | M_EMOTE_EXTREME,

    "gag"                 : M_EMOTE_NEUTRAL,
    "gasp"                : M_EMOTE_NEUTRAL,
    "gesture"             : M_EMOTE_NEUTRAL,
    "giggle"              : M_EMOTE_FRIENDSHIP | M_EMOTE_MILD,
    "glare"               : M_EMOTE_HOSTILITY,
    "greet"               : M_EMOTE_POLITENESS,
    "grimace"             : M_EMOTE_NEUTRAL,
    "grin"                : M_EMOTE_NEUTRAL,
    "groan"               : M_EMOTE_NEUTRAL,
    "grope"               : M_EMOTE_NEUTRAL,
    "grovel"              : M_EMOTE_DEBASEMENT | M_EMOTE_EXTREME,
    "growl"               : M_EMOTE_HOSTILITY,
    "grumble"             : M_EMOTE_DISAGREEMENT | M_EMOTE_MILD,
    "grunt"               : M_EMOTE_NEUTRAL,

    "hang"                : M_EMOTE_POLITENESS,
    "hbrush"              : M_EMOTE_NEUTRAL,
    "hhug"                : M_EMOTE_FRIENDSHIP,
    "hiccup"              : M_EMOTE_NEUTRAL,
    "hlook"               : M_EMOTE_NEUTRAL,
    "hmm"                 : M_EMOTE_NEUTRAL,
    "hold"                : M_EMOTE_FONDNESS,
    "hthrash"             : M_EMOTE_NEUTRAL,
    "htoss"               : M_EMOTE_NEUTRAL,
    "hug"                 : M_EMOTE_FRIENDSHIP,
    "hum"                 : M_EMOTE_NEUTRAL,
    "hwash"               : M_EMOTE_NEUTRAL,

    "ignore"              : M_EMOTE_HOSTILITY,
    "invite"              : M_EMOTE_FRIENDSHIP,

    "jump"                : M_EMOTE_NEUTRAL,

    "kexcuse"             : M_EMOTE_NEUTRAL,
    "kick"                : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "kiss"                : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "knee"                : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "kneel"               : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,
    "kstifle"             : M_EMOTE_FRIENDSHIP | M_EMOTE_MILD,
    "kstudy"              : M_EMOTE_NEUTRAL,

    "laugh"               : M_EMOTE_NEUTRAL,
    "leer"                : M_EMOTE_NEUTRAL,
    "lick"                : M_EMOTE_FONDNESS,
    "listen"              : M_EMOTE_POLITENESS,
    "love"                : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,

    "mbless"              : M_EMOTE_FRIENDSHIP,
    "mbow"                : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,
    "mcenter"             : M_EMOTE_NEUTRAL,
    "mclean"              : M_EMOTE_NEUTRAL,
    "melt"                : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "mgreet"              : M_EMOTE_POLITENESS,
    "mhonor"              : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,
    "mk"                  : M_EMOTE_UNKNOWN,
    "mkill"               : M_EMOTE_HOSTILITY,
    "mlook"               : M_EMOTE_NEUTRAL,
    "moan"                : M_EMOTE_NEUTRAL,
    "mourn"               : M_EMOTE_POLITENESS,
    "mrelax"              : M_EMOTE_NEUTRAL,
    "msketch"             : M_EMOTE_FRIENDSHIP,
    "mstep"               : M_EMOTE_POLITENESS,
    "mumble"              : M_EMOTE_DISAGREEMENT | M_EMOTE_MILD,
    "mwarn"               : M_EMOTE_HOSTILITY,

    "nibble"              : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "nod"                 : M_EMOTE_POLITENESS | M_EMOTE_MILD,
    "nudge"               : M_EMOTE_NEUTRAL,
    "nuzzle"              : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,

    "oops"                : M_EMOTE_NEUTRAL,
    "ouch"                : M_EMOTE_NEUTRAL,

    "pace"                : M_EMOTE_NEUTRAL,
    "panic"               : M_EMOTE_NEUTRAL,
    "pant"                : M_EMOTE_NEUTRAL,
    "pat"                 : M_EMOTE_FONDNESS,
    "pbestow"             : M_EMOTE_FRIENDSHIP,
    "peer"                : M_EMOTE_NEUTRAL,
    "pet"                 : M_EMOTE_FONDNESS,
    "pfarewell"           : M_EMOTE_POLITENESS,
    "pgreet"              : M_EMOTE_POLITENESS,
    "pguide"              : M_EMOTE_POLITENESS,
    "pinch"               : M_EMOTE_FONDNESS,
    "plaugh"              : M_EMOTE_NEUTRAL,
    "point"               : M_EMOTE_NEUTRAL,
    "poke"                : M_EMOTE_NEUTRAL,
    "ponder"              : M_EMOTE_NEUTRAL,
    "pounce"              : M_EMOTE_FRIENDSHIP,
    "pout"                : M_EMOTE_NEUTRAL,
    "puke"                : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "purr"                : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,

    "rbearing"            : M_EMOTE_NEUTRAL,
    "rbow"                : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,
    "rcurtsey"            : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,
    "respect"             : M_EMOTE_POLITENESS,
    "rhail"               : M_EMOTE_POLITENESS,
    "rinspect"            : M_EMOTE_NEUTRAL,
    "roar"                : M_EMOTE_NEUTRAL,
    "rolleyes"            : M_EMOTE_NEUTRAL,
    "ruffle"              : M_EMOTE_FONDNESS,
    "rwipe"               : M_EMOTE_NEUTRAL,

    "scold"               : M_EMOTE_DISAGREEMENT | M_EMOTE_EXTREME,
    "scowl"               : M_EMOTE_HOSTILITY,
    "scratch"             : M_EMOTE_NEUTRAL,
    "scream"              : M_EMOTE_NEUTRAL,
    "sfare"               : M_EMOTE_POLITENESS,
    "sgrin"               : M_EMOTE_NEUTRAL,
    "shake"               : M_EMOTE_NEUTRAL,
    "shiver"              : M_EMOTE_NEUTRAL,
    "shout"               : M_EMOTE_NEUTRAL,
    "show"                : M_EMOTE_NEUTRAL,
    "shrug"               : M_EMOTE_NEUTRAL,
    "shudder"             : M_EMOTE_NEUTRAL,
    "sigh"                : M_EMOTE_NEUTRAL,
    "sing"                : M_EMOTE_NEUTRAL,
    "slap"                : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "smell"               : M_EMOTE_NEUTRAL,
    "smile"               : M_EMOTE_FRIENDSHIP,
    "smirk"               : M_EMOTE_HOSTILITY,
    "snap"                : M_EMOTE_NEUTRAL,
    "snarl"               : M_EMOTE_HOSTILITY,
    "sneer"               : M_EMOTE_HOSTILITY,
    "sneeze"              : M_EMOTE_NEUTRAL,
    "snicker"             : M_EMOTE_NEUTRAL,
    "sniff"               : M_EMOTE_NEUTRAL,
    "snore"               : M_EMOTE_NEUTRAL,
    "snuggle"             : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "sob"                 : M_EMOTE_NEUTRAL,
    "spank"               : M_EMOTE_FONDNESS,
    "spit"                : M_EMOTE_HOSTILITY | M_EMOTE_EXTREME,
    "squeeze"             : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "squirm"              : M_EMOTE_NEUTRAL,
    "stare"               : M_EMOTE_NEUTRAL,
    "startle"             : M_EMOTE_NEUTRAL,
    "steam"               : M_EMOTE_NEUTRAL,
    "stick"               : M_EMOTE_NEUTRAL,
    "stomp"               : M_EMOTE_NEUTRAL,
    "stretch"             : M_EMOTE_NEUTRAL,
    "strut"               : M_EMOTE_NEUTRAL,
    "stumble"             : M_EMOTE_NEUTRAL,
    "sulk"                : M_EMOTE_NEUTRAL,
    "swallow"             : M_EMOTE_NEUTRAL,
    "swear"               : M_EMOTE_HOSTILITY,
    "sweat"               : M_EMOTE_NEUTRAL,
    "swoon"               : M_EMOTE_FONDNESS,

    "tackle"              : M_EMOTE_NEUTRAL,
    "tap"                 : M_EMOTE_NEUTRAL,
    "tcross"              : M_EMOTE_NEUTRAL,
    "tease"               : M_EMOTE_FONDNESS | M_EMOTE_MILD,
    "tfare"               : M_EMOTE_POLITENESS,
    "tgreet"              : M_EMOTE_POLITENESS,
    "thank"               : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,
    "think"               : M_EMOTE_NEUTRAL,
    "thumb"               : M_EMOTE_ADMIRATION,
    "tickle"              : M_EMOTE_FONDNESS | M_EMOTE_MILD,
    "tingle"              : M_EMOTE_NEUTRAL,
    "tnod"                : M_EMOTE_POLITENESS | M_EMOTE_MILD,
    "touch"               : M_EMOTE_FONDNESS,
    "tremble"             : M_EMOTE_DEBASEMENT,
    "trust"               : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "tug"                 : M_EMOTE_NEUTRAL,
    "twave"               : M_EMOTE_POLITENESS,
    "twiddle"             : M_EMOTE_NEUTRAL,
    "twinkle"             : M_EMOTE_NEUTRAL,
    "twitch"              : M_EMOTE_NEUTRAL,

    "ubow"                : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,

    "wail"                : M_EMOTE_NEUTRAL,
    "wait"                : M_EMOTE_NEUTRAL,
    "wave"                : M_EMOTE_POLITENESS,
    "wbless"              : M_EMOTE_FRIENDSHIP,
    "wchant"              : M_EMOTE_NEUTRAL,
    "weep"                : M_EMOTE_NEUTRAL,
    "wgaze"               : M_EMOTE_NEUTRAL,
    "whimper"             : M_EMOTE_NEUTRAL,
    "whine"               : M_EMOTE_NEUTRAL,
    "whisper"             : M_EMOTE_FONDNESS | M_EMOTE_MILD,
    "whistle"             : M_EMOTE_NEUTRAL,
    "wiggle"              : M_EMOTE_NEUTRAL,
    "wince"               : M_EMOTE_NEUTRAL,
    "wink"                : M_EMOTE_FONDNESS | M_EMOTE_MILD,
    "wonder"              : M_EMOTE_NEUTRAL,
    "worry"               : M_EMOTE_FRIENDSHIP,
    "worship"             : M_EMOTE_ADMIRATION | M_EMOTE_EXTREME,
    "wring"               : M_EMOTE_NEUTRAL,

    "yawn"                : M_EMOTE_HOSTILITY,
    "yodel"               : M_EMOTE_NEUTRAL,
    
    "ask"                 : M_EMOTE_NEUTRAL,
    "dkiss"               : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "ethwap"              : M_EMOTE_HOSTILITY,
    "eyeroll"             : M_EMOTE_NEUTRAL,
    "eyestare"            : M_EMOTE_NEUTRAL,
    "fgrin"               : M_EMOTE_NEUTRAL,
    "flaugh"              : M_EMOTE_NEUTRAL,
    "grecite"             : M_EMOTE_NEUTRAL,
    "gturn"               : M_EMOTE_NEUTRAL,
    "guffaw"              : M_EMOTE_NEUTRAL,
    "hbow"                : M_EMOTE_POLITENESS | M_EMOTE_EXTREME,
    "kbye"                : M_EMOTE_POLITENESS,
    "kclasp"              : M_EMOTE_FRIENDSHIP,
    "mdisdain"            : M_EMOTE_HOSTILITY,
    "mhail"               : M_EMOTE_NEUTRAL, /*Mages - Not entirely friendly*/
    "mmight"              : M_EMOTE_HOSTILITY,
    "moath"               : M_EMOTE_NEUTRAL,
    "mrecall"             : M_EMOTE_NEUTRAL,
    "mrecite"             : M_EMOTE_NEUTRAL,
    "mhumble"             : M_EMOTE_POLITENESS,
    "sbless"              : M_EMOTE_POLITENESS,
    "shug"                : M_EMOTE_FRIENDSHIP,
    "tcfrench"            : M_EMOTE_FONDNESS | M_EMOTE_EXTREME,
    "team"                : M_EMOTE_FRIENDSHIP,
  ]);

  // The classification of adverbs is somewhat more difficult because
  // the categories of emotes do not quite apply. But imagine someone
  // grinning or smiling with the adverb and filter out adverbs that
  // do not necessarily describe attitudes to people ...

  // Remember that the MILD and EXTREME classifiers should not be used here.

  mapping miAdverbs = ([

    "admiringly"                  : M_EMOTE_ADMIRATION,
    "adoringly"                   : M_EMOTE_ADMIRATION,
    "again"                       : M_EMOTE_NEUTRAL,
    "agreeably"                   : M_EMOTE_POLITENESS,
    "airily"                      : M_EMOTE_HOSTILITY,
    "amusedly"                    : M_EMOTE_NEUTRAL,
    "angrily"                     : M_EMOTE_HOSTILITY,
    "annoyedly"                   : M_EMOTE_HOSTILITY,
    "apologetically"              : M_EMOTE_POLITENESS,
    "appreciatively"              : M_EMOTE_ADMIRATION,
    "approvingly"                 : M_EMOTE_ADMIRATION,
    "arrogantly"                  : M_EMOTE_HOSTILITY,
    "as if something is wrong"    : M_EMOTE_NEUTRAL,

    "back"                        : M_EMOTE_NEUTRAL,
    "briefly"                     : M_EMOTE_NEUTRAL,
    "brightly"                    : M_EMOTE_NEUTRAL,
    "broadly"                     : M_EMOTE_NEUTRAL,
    "brotherly"                   : M_EMOTE_FRIENDSHIP,

    "challengingly"               : M_EMOTE_DISAGREEMENT,
    "contemptuously"              : M_EMOTE_HOSTILITY,
    "cordially"                   : M_EMOTE_FRIENDSHIP,
    "curiously"                   : M_EMOTE_NEUTRAL,

    "deeply"                      : M_EMOTE_POLITENESS,
    "degradingly"                 : M_EMOTE_HOSTILITY,
    "delightedly"                 : M_EMOTE_NEUTRAL,
    "derisively"                  : M_EMOTE_HOSTILITY,
    "devotedly"                   : M_EMOTE_ADMIRATION,
    "disgustedly"                 : M_EMOTE_HOSTILITY,
    "dishonestly"                 : M_EMOTE_HOSTILITY,
    "dishonourably"               : M_EMOTE_HOSTILITY,
    "disrespectfully"             : M_EMOTE_HOSTILITY,
    "dramatically"                : M_EMOTE_NEUTRAL,

    "earnestly"                   : M_EMOTE_ADMIRATION,
    "embarrassedly"               : M_EMOTE_POLITENESS,
    "encouragingly"               : M_EMOTE_FRIENDSHIP,
    "enthusiastically"            : M_EMOTE_FRIENDSHIP,
    "evilly"                      : M_EMOTE_NEUTRAL,
    "excessively"                 : M_EMOTE_NEUTRAL,
    "expectantly"                 : M_EMOTE_NEUTRAL,
    "exuberantly"                 : M_EMOTE_NEUTRAL,

    "faintly"                     : M_EMOTE_NEUTRAL,
    "from the cold"               : M_EMOTE_NEUTRAL,
    "frostily"                    : M_EMOTE_HOSTILITY,

    "gallantly"                   : M_EMOTE_POLITENESS,
    "generously"                  : M_EMOTE_FRIENDSHIP,
    "gently"                      : M_EMOTE_FONDNESS,
    "gracefully"                  : M_EMOTE_NEUTRAL,
    "graciously"                  : M_EMOTE_FRIENDSHIP,
    "grandiosely"                 : M_EMOTE_NEUTRAL,
    "gratefully"                  : M_EMOTE_POLITENESS,

    "happily"                     : M_EMOTE_NEUTRAL,
    "harshly"                     : M_EMOTE_HOSTILITY,
    "haughtily"                   : M_EMOTE_HOSTILITY,
    "heartlessly"                 : M_EMOTE_HOSTILITY,
    "helplessly"                  : M_EMOTE_NEUTRAL,
    "hesitantly"                  : M_EMOTE_NEUTRAL,
    "honestly"                    : M_EMOTE_POLITENESS,
    "honourably"                  : M_EMOTE_POLITENESS,
    "hopefully"                   : M_EMOTE_NEUTRAL,
    "humbly"                      : M_EMOTE_POLITENESS,
    "hurriedly"                   : M_EMOTE_NEUTRAL,

    "impatiently"                 : M_EMOTE_NEUTRAL,
    "in a friendly manner"        : M_EMOTE_FRIENDSHIP,
    "in a subtle manner"          : M_EMOTE_POLITENESS,
    "in acknowledgement"          : M_EMOTE_POLITENESS,
    "in explanation"              : M_EMOTE_POLITENESS,
    "innocently"                  : M_EMOTE_NEUTRAL,
    "inquisitively"               : M_EMOTE_NEUTRAL,
    "intentionally"               : M_EMOTE_NEUTRAL,
    "irritably"                   : M_EMOTE_HOSTILITY,

    "joyfully"                    : M_EMOTE_FONDNESS,
    "joyously"                    : M_EMOTE_FONDNESS,

    "kindly"                      : M_EMOTE_FONDNESS,
    "knowingly"                   : M_EMOTE_NEUTRAL,

    "like acid"                   : M_EMOTE_HOSTILITY,
    "loftily"                     : M_EMOTE_HOSTILITY,
    "lovingly"                    : M_EMOTE_FONDNESS,

    "maliciously"                 : M_EMOTE_HOSTILITY,
    "mercifully"                  : M_EMOTE_FONDNESS,
    "mercilessly"                 : M_EMOTE_HOSTILITY,
    "merrily"                     : M_EMOTE_NEUTRAL,
    "mischievously"               : M_EMOTE_NEUTRAL,
    "modestly"                    : M_EMOTE_POLITENESS,

    "nastily"                     : M_EMOTE_HOSTILITY,
    "nicely"                      : M_EMOTE_FONDNESS,

    "obscenely"                   : M_EMOTE_HOSTILITY,

    "patiently"                   : M_EMOTE_POLITENESS,
    "patronizingly"               : M_EMOTE_HOSTILITY,
    "peacefully"                  : M_EMOTE_POLITENESS,
    "playfully"                   : M_EMOTE_FONDNESS,
    "pleadingly"                  : M_EMOTE_POLITENESS,
    "politely"                    : M_EMOTE_POLITENESS,
    "pompously"                   : M_EMOTE_HOSTILITY,
    "pretentiously"               : M_EMOTE_HOSTILITY,

    "quietly"                     : M_EMOTE_NEUTRAL,
    "quizzically"                 : M_EMOTE_NEUTRAL,

    "respectfully"                : M_EMOTE_POLITENESS,
    "rudely"                      : M_EMOTE_HOSTILITY,
    "ruthlessly"                  : M_EMOTE_HOSTILITY,

    "sadistically"                : M_EMOTE_HOSTILITY,
    "sadly"                       : M_EMOTE_NEUTRAL,
    "savagely"                    : M_EMOTE_NEUTRAL,
    "scornfully"                  : M_EMOTE_HOSTILITY,
    "secretively"                 : M_EMOTE_NEUTRAL,
    "selfishly"                   : M_EMOTE_HOSTILITY,
    "sensually"                   : M_EMOTE_NEUTRAL,
    "seriously"                   : M_EMOTE_NEUTRAL,
    "shamelessly"                 : M_EMOTE_HOSTILITY,
    "sheepishly"                  : M_EMOTE_NEUTRAL,
    "shiftily"                    : M_EMOTE_HOSTILITY,
    "sincerely"                   : M_EMOTE_FRIENDSHIP,
    "sinfully"                    : M_EMOTE_HOSTILITY,
    "sinisterly"                  : M_EMOTE_HOSTILITY,
    "slightly"                    : M_EMOTE_NEUTRAL,
    "slowly"                      : M_EMOTE_NEUTRAL,
    "slyly"                       : M_EMOTE_HOSTILITY,
    "smilingly"                   : M_EMOTE_FRIENDSHIP,
    "sneakily"                    : M_EMOTE_HOSTILITY,
    "softly"                      : M_EMOTE_NEUTRAL,
    "solemnly"                    : M_EMOTE_NEUTRAL,
    "soothingly"                  : M_EMOTE_FRIENDSHIP,
    "spitefully"                  : M_EMOTE_HOSTILITY,
    "suggestively"                : M_EMOTE_NEUTRAL,
    "supportively"                : M_EMOTE_FRIENDSHIP,
    "suspiciously"                : M_EMOTE_NEUTRAL,
    "sweetly"                     : M_EMOTE_FONDNESS,

    "thankfully"                  : M_EMOTE_POLITENESS,
    "theatrically"                : M_EMOTE_HOSTILITY,
    "thoughtfully"                : M_EMOTE_NEUTRAL,
    "threateningly"               : M_EMOTE_HOSTILITY,
    "tightly"                     : M_EMOTE_NEUTRAL,
    "totally"                     : M_EMOTE_NEUTRAL,
    "trustfully"                  : M_EMOTE_FRIENDSHIP,

    "unashamedly"                 : M_EMOTE_HOSTILITY,
    "uncaringly"                  : M_EMOTE_HOSTILITY,
    "uncomfortably"               : M_EMOTE_NEUTRAL,
    "uncontrollably"              : M_EMOTE_NEUTRAL,
    "understandingly"             : M_EMOTE_NEUTRAL,
    "unexpectedly"                : M_EMOTE_NEUTRAL,
    "unhappily"                   : M_EMOTE_NEUTRAL,
    "unmercifully"                : M_EMOTE_HOSTILITY,

    "viciously"                   : M_EMOTE_HOSTILITY,
    "violently"                   : M_EMOTE_HOSTILITY,

    "warmly"                      : M_EMOTE_FONDNESS,
    "weakly"                      : M_EMOTE_NEUTRAL,
    "wearily"                     : M_EMOTE_NEUTRAL,
    "wholeheartedly"              : M_EMOTE_ADMIRATION,
    "wickedly"                    : M_EMOTE_NEUTRAL,
    "wildly"                      : M_EMOTE_NEUTRAL,
    "wisely"                      : M_EMOTE_POLITENESS,
    "with glee"                   : M_EMOTE_NEUTRAL,
    "worriedly"                   : M_EMOTE_NEUTRAL,
    
    "carefully"                   : M_EMOTE_NEUTRAL,
    "closely"                     : M_EMOTE_FONDNESS,
    "deafeningly"                 : M_EMOTE_HOSTILITY,
    "fanatically"                 : M_EMOTE_NEUTRAL,
    "in anticipation"             : M_EMOTE_NEUTRAL,
    "impressively"                : M_EMOTE_HOSTILITY,
    "pitifully"                   : M_EMOTE_NEUTRAL,
    "profusely"                   : M_EMOTE_NEUTRAL,
    "stupidly"                    : M_EMOTE_NEUTRAL,
    "reverently"                  : M_EMOTE_POLITENESS,
    "wistfully"                   : M_EMOTE_NEUTRAL,
  ]);

  object oSoul;
  int iEmoteClass;
  int iAdverbClass;
  int iClassification;

  // First the emote is classified. The classification is based on
  // the hardcoded list and on the attributes if the emote is not
  // listed or is listed as unknown. A pity the attributes are
  // pretty much unreliable.

  // This relies on the fact that indexing a mapping with
  // a nonexistent key returns zero ...

  if (strlen (sEmote)) iEmoteClass = miEmotes [sEmote];
                  else iEmoteClass = M_EMOTE_UNKNOWN;

  if (iEmoteClass == 0)
  {
    oSoul = m_get_emote_soul (oActor, sEmote);
    if (oSoul) s_log (M_LOG_DEBUG, "Unknown emote \"" + sEmote + "\" from " + MASTER_OB (oSoul) + ".");
          else s_log (M_LOG_DEBUG, "Unknown emote \"" + sEmote + "\".");
    iEmoteClass = M_EMOTE_UNKNOWN;
  }

  if (iEmoteClass == M_EMOTE_UNKNOWN)
  {
    if (iAttributes & ACTION_INTIMATE)     iEmoteClass |= M_EMOTE_FONDNESS;
    if (iAttributes & ACTION_OFFENSIVE)    iEmoteClass |= M_EMOTE_HOSTILITY;
    if (iAttributes & ACTION_THREATENING)  iEmoteClass |= M_EMOTE_HOSTILITY;
    if (iAttributes & ACTION_INGRATIATORY) iEmoteClass |= M_EMOTE_ADMIRATION;
  }

  // Second the adverb is classified. The classification
  // is based on the hardcoded list only.

  if (strlen (sAdverb)) iAdverbClass = miAdverbs [sAdverb];
                   else iAdverbClass = M_EMOTE_UNKNOWN;

  if (iAdverbClass == 0)
  {
    oSoul = m_get_emote_soul (oActor, sEmote);
    if (oSoul) s_log (M_LOG_DEBUG, "Unknown adverb \"" + sAdverb + "\" from " + MASTER_OB (oSoul) + ".");
          else s_log (M_LOG_DEBUG, "Unknown adverb \"" + sAdverb + "\".");
    iAdverbClass = M_EMOTE_UNKNOWN;
  }

  // Now to make some sense of the combination of emote and adverb. Note that
  // some of the expressions and branches could be optimized but the result
  // is less readable and less changeable.

  iClassification = 0;

  // Emotes that signify fondness, admiration, friendship and politeness.

  if (iEmoteClass & (M_EMOTE_FONDNESS | M_EMOTE_ADMIRATION | M_EMOTE_FRIENDSHIP | M_EMOTE_POLITENESS))
  {
    if (iAdverbClass & (M_EMOTE_FONDNESS | M_EMOTE_ADMIRATION | M_EMOTE_FRIENDSHIP | M_EMOTE_POLITENESS))
    {
      // Emotes that signify fondness, admiration, friendship and politeness
      // accompanied by a similar adverb get strenghtened and merge with the
      // meaning of the adverb.

      if (iEmoteClass & M_EMOTE_MILD)
        iClassification |= (iEmoteClass | iAdverbClass) & ~M_EMOTE_MILD;
      else
        iClassification |= iEmoteClass | iAdverbClass | M_EMOTE_EXTREME;
    }
    else if (iAdverbClass & (M_EMOTE_HOSTILITY | M_EMOTE_DEBASEMENT))
    {
      // Emotes that signify fondness, admiration, friendship and politeness
      // accompanied by a hostile or debasing adverb take over the meaning
      // of the adverb but somewhat soften its strength.

      if (iEmoteClass & M_EMOTE_MILD)
        iClassification |= iAdverbClass | M_EMOTE_EXTREME;
      else if (iEmoteClass & M_EMOTE_EXTREME)
        iClassification |= iAdverbClass | M_EMOTE_MILD;
      else
        iClassification |= iAdverbClass;
    }
    else if (iAdverbClass & M_EMOTE_DISAGREEMENT)
    {
      // Emotes that signify fondness, admiration, friendship and politeness
      // accompanied by a disagreeing adverb get weakened, except for mild
      // emotes that take over the meaning of the adverb.

      if (iEmoteClass & M_EMOTE_MILD)
        iClassification |= iAdverbClass | M_EMOTE_MILD;
      else
        iClassification |= (iEmoteClass | M_EMOTE_MILD) & ~M_EMOTE_EXTREME;
    }
    else iClassification |= iEmoteClass;
  }

  // Emotes that signify hostility.

  if (iEmoteClass & M_EMOTE_HOSTILITY)
  {
    if (iAdverbClass & (M_EMOTE_FONDNESS | M_EMOTE_ADMIRATION | M_EMOTE_FRIENDSHIP | M_EMOTE_POLITENESS))
    {
      // Emotes that signify hostility accompanied by a fond, admiring,
      // friendly or polite adverb disregard the adverb, except for mild
      // emotes that take over the meaning of the adwerb.

      if (iEmoteClass & M_EMOTE_MILD)
        iClassification |= iAdverbClass | M_EMOTE_MILD;
      else
        iClassification |= iEmoteClass;
    }
    else if (iAdverbClass & (M_EMOTE_HOSTILITY | M_EMOTE_DEBASEMENT | M_EMOTE_DISAGREEMENT))
    {
      // Emotes that signify hostility accompanied by an hostile,
      // debasing or disagreeing adverb are strenghtened and merge
      // with the meaning of the adverb.

      if (iEmoteClass & M_EMOTE_MILD)
        iClassification |= (iEmoteClass | iAdverbClass) & ~M_EMOTE_MILD;
      else
        iClassification |= iEmoteClass | iAdverbClass | M_EMOTE_EXTREME;
    }
    else iClassification |= iEmoteClass;
  }

  // Emotes that signify debasement.

  if (iEmoteClass & M_EMOTE_DEBASEMENT)
  {
    if (iAdverbClass & (M_EMOTE_FONDNESS | M_EMOTE_ADMIRATION | M_EMOTE_FRIENDSHIP | M_EMOTE_POLITENESS))
    {
      // Emotes that signify debasement accompanied by a fond, admiring,
      // friendly or polite adverb disregard the adverb, except for mild
      // emotes that take over the meaning of the adwerb.

      if (iEmoteClass & M_EMOTE_MILD)
        iClassification |= iAdverbClass | M_EMOTE_MILD;
      else
        iClassification |= iEmoteClass;
    }
    else if (iAdverbClass & (M_EMOTE_HOSTILITY | M_EMOTE_DISAGREEMENT))
    {
      // Emotes that signify debasement accompanied by a hostile or
      // or disagreeing adverb merge with the meaning of the adverb.

      iClassification |= iEmoteClass | iAdverbClass;
    }
    else if (iAdverbClass & M_EMOTE_DEBASEMENT)
    {
      // Emotes that signify debasement accompanied by a debasing,
      // adverb are strenghtened.

      if (iEmoteClass & M_EMOTE_MILD)
        iClassification |= iEmoteClass & ~M_EMOTE_MILD;
      else
        iClassification |= iEmoteClass | M_EMOTE_EXTREME;
    }
    else iClassification |= iEmoteClass;
  }

  // Emotes that signify disagreement.

  if (iEmoteClass & M_EMOTE_DISAGREEMENT)
  {
    if (iAdverbClass & (M_EMOTE_FONDNESS | M_EMOTE_ADMIRATION | M_EMOTE_FRIENDSHIP | M_EMOTE_POLITENESS))
    {
      // Emotes that signify disagreement accompanied by a fond, admiring,
      // friendly or polite adverb take over the meaning of the adverb.

      iClassification |= iAdverbClass | M_EMOTE_MILD;
    }
    else if (iAdverbClass & (M_EMOTE_HOSTILITY | M_EMOTE_DEBASEMENT | M_EMOTE_DISAGREEMENT))
    {
      // Emotes that signify disagreement accompanied by a hostile,
      // debasing or disagreeing adverb are strenghtened and merge
      // with the meaning of the adverb.

      if (iEmoteClass & M_EMOTE_MILD)
        iClassification |= (iEmoteClass | iAdverbClass) & ~M_EMOTE_MILD;
      else
        iClassification |= iEmoteClass | iAdverbClass | M_EMOTE_EXTREME;
    }
    else iClassification |= iEmoteClass;
  }

  // Neutral emotes take over the meaning of the adverb if there is any.

  if ((iEmoteClass & M_EMOTE_NEUTRAL) & !(iAdverbClass & (M_EMOTE_UNKNOWN | M_EMOTE_NEUTRAL)))
  {
    iClassification |= iAdverbClass | M_EMOTE_MILD;
  }

  // Not arriving at a classification by now is a bug.

  if (!iClassification &&
      !(iEmoteClass & (M_EMOTE_UNKNOWN | M_EMOTE_NEUTRAL)) &&
      !(iAdverbClass & (M_EMOTE_UNKNOWN | M_EMOTE_NEUTRAL)))
  {
      s_log (M_LOG_DEBUG, "Unable to classify emote \"" + sEmote + "\" with adverb \"" + sAdverb + "\".");
  }

  // This is here for watching what it is that the function returns
  // so that one can make sure it makes at least a little sense.

  // s_log (M_LOG_DEBUG, "Classification of \"" + sEmote + "\" \"" + sAdverb + "\" is" +
  //                     (iClassification == 0 ? " NONE" : "") +
  //                     (iClassification & M_EMOTE_UNKNOWN ? " UNKNOWN" : "") +
  //                     (iClassification & M_EMOTE_NEUTRAL ? " NEUTRAL" : "") +
  //                     (iClassification & M_EMOTE_MILD ? " MILD" : "") +
  //                     (iClassification & M_EMOTE_EXTREME ? " EXTREME" : "") +
  //                     (iClassification & M_EMOTE_FONDNESS ? " FONDNESS" : "") +
  //                     (iClassification & M_EMOTE_HOSTILITY ? " HOSTILITY" : "") +
  //                     (iClassification & M_EMOTE_ADMIRATION ? " ADMIRATION" : "") +
  //                     (iClassification & M_EMOTE_DEBASEMENT ? " DEBASEMENT" : "") +
  //                     (iClassification & M_EMOTE_FRIENDSHIP ? " FRIENDSHIP" : "") +
  //                     (iClassification & M_EMOTE_POLITENESS ? " POLITENESS" : "") +
  //                     (iClassification & M_EMOTE_DISAGREEMENT ? " DISAGREEMENT" : "") +
  //                     ".");

  // ... whatever it is we are returning.

  return (iClassification);
}

//-------------------------------------------------------------------

