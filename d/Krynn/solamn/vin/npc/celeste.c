/*
Celeste Softsulle
The bard who sings tunes for people in the Bronze Dragon Inn
by Teth, March 29, 1996
modified from Jeremiah's Verminaard 
   */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <macros.h>
#include "../local.h";
inherit M_FILE

inherit "/std/act/action";

#include "killer.h"

int cloned;

void
create_krynn_monster()
{
    string str;

    set_name("celeste");
    set_living_name("celeste");
    set_race_name("human");
    set_title("Softsulle, Bard of Vingaard Keep");
    set_long("This woman is not a ravishing beauty, but she has a tender and "+
      "gentle aura about her. Her hair is a rich brown colour, "+
      "and is shoulder length. She has doe-brown eyes, that sparkle "+
      "in the light of the Inn. Her body is thin, with hips that are "+
      "not too wide for her height, which is small. She carries an "+
      "ancient-looking lyre, that performs beautiful music in her "+
      "supple hands.\n"); 
    add_name(({"bard", "minstrel"}));
    set_adj("waifish");
    add_adj("compassionate"); 
    set_gender(G_FEMALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_WEIGHT, 20000);
    set_introduce(1);

    cloned = 0;
    set_stats(({54,68,58,88,86,49}));
    set_skill(SS_DEFENCE,        25);
    set_skill(SS_PARRY,          25);  
    set_skill(SS_UNARM_COMBAT,   30);
    set_skill(SS_AWARENESS,      40);
    add_prop(NPC_I_NO_RUN_AWAY,  1);

    set_alignment(653);
    set_knight_prestige(-4);

    set_all_hitloc_unarmed(10);

    set_act_time(7);
    add_act("emote hums a soft tune to herself.");
    add_act("emote delicately strums her lyre.");
    add_act("sigh dreamily");
    add_act("emote thoughtfully combs her long hair back over her ear " +
      "with her right hand.");
    add_act("emote inhales softly.");
    add_act("emote murmurs softly to herself, apparently reciting words.");
    add_act("emote looks off into the distance as she thinks of tales of " +
      "high adventure and heroism.");

    set_cact_time(6);
    add_cact("shout Help! I am being attacked!");
    add_cact("emote plaintively cries: Why me? Why?");
    add_cact("shout Someone! Please help me!");

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] [song] [of] 'huma'","@@huma_song", 1);
    add_ask(" [about] [canticle] [of] [the] 'dragon' / 'canticle'",
      "@@canticle_song", 1);
    add_ask(" [about] [death] 'chant'",
      "@@death_chant", 1);
    add_ask(" [about] 'song' / 'songs' / 'sing'","say People have made " +
      "many requests of me for songs...which one would you like "+
      "to request?", 1);
    add_ask(" [about] 'request' / 'requests'","say I have had "+
      "requests for parts of the Song of Huma, I know the first "+
      "portion of the Canticle of the Dragon, and, also, I know "+
      "the Death Chant of the Solamnic Knights.", 1);

}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    command("shout Somebody help me! I'm under attack!");
    seteuid(getuid());
    if (cloned == 0)
        clone_object(VNPC + "stephen")->move(environment());
    cloned = 1;
}

string
huma_song()
{
    set_alarm(1.0,0.0,"command","say Alas, most of that song has " +
      "been lost in the tides of time. I shall sing what I know, " +
      "though.");
    set_alarm(5.0,0.0,"command","emote dances her fingers over her lyre, " +
      "ensuring that it is in tune.\n");
    set_alarm(9.0,0.0,"command",
      "emote softly sings:\n\n"+
      "   It was there and then that the White Stag found him,\n"+
      "   At the end of a journey planned from the shores of Creation,\n"+
      "   And all time staggered at the forest edge\n"+
      "   Where Huma, haunted and starving,\n"+
      "   Drew his bow, thanking the gods for their bounty and keeping,\n"+
      "   Then saw, in the ranged wood,\n"+
      "   In the first silence, the dazed heart's symbol,\n"+
      "   The rack of antlers resplendent.\n"+
      "   He lowered the bow and the world resumed.\n"+
      "   Then Huma followed the Stag, its tangle of antlers receding\n"+
      "   As a memory of young light, as the talons of birds ascending.\n"+
      "   The Mountain crouched before them. Nothing would change now,\n"+
      "   The three moons stopped in the sky,\n"+
      "   And the long night tumbled in the shadows.\n");
    set_alarm(39.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Stunned in new freedom, stunned by the brightness and colours,\n"+
      "   By the harped blessings of the holy winds,\n"+
      "   The Knights carried Huma, they carried the Dragonlance\n"+
      "   To the grove in the lap of the Mountain.\n"+
      "   When they returned to the grove in pilgrimage, in homage,\n"+
      "   The Lance, the armour, the Dragonbane himself\n"+
      "   Had vanished to the day's eye.\n"+
      "   But the night of the full moons red and silver\n"+
      "   Shines down on the hills, on the forms of a man and a woman\n"+
      "   Shimmering steel and silver, silver and steel,\n"+
      "   Above the village, over the thatched and nurturing shires.\n");
    set_alarm(69.0,0.0,"command","say That was the second and the final " +
      "verse. Tis all I know. It is such a sad and glorious song.");
    set_alarm(71.0,0.0,"command","sigh sadly");
    
    return "";
}

string
canticle_song()
{
    set_alarm(1.0,0.0,"command","say The Canticle of the Dragon? I shall " +
      "play the first part for you. I am still learning the second " +
      "portion of the song.");
    set_alarm(3.0,0.0,"command","emote plucks the strings of her lyre to " +
      "check if it still in tune.\n");
    set_alarm(6.0,0.0,"command",
      "emote sings:\n\n"+
      "   Hear the sage as his song descends\n"+
      "   like heaven's rain or tears,\n"+
      "   and washes the years, the dust of the many stories\n"+
      "   from the High Tale of the Dragonlance.\n"+
      "   For in ages deep, past memory and word,\n"+
      "   in the first blush of the world\n"+
      "   when the three moons rose from the lap of the forest,\n"+
      "   dragons, terrible and great,\n"+
      "   made war on this world of Krynn.\n");

    set_alarm(21.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Yet out of the darkness of dragons,\n"+
      "   out of our cries for light\n"+
      "   in the blank face of the black moon soaring,\n"+
      "   a banked light flared in Solamnia,\n"+
      "   a knight of truth and power,\n"+
      "   who called down the gods themselves\n"+
      "   and forged the mighty Dragonlance, piercing the soul\n"+
      "   of dragonkind, driving the shade of their wings\n"+
      "   from the brightening shores of Krynn.\n");

    set_alarm(36.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Thus Huma, Knight of Solamnia,\n"+
      "   Lightbringer, First Lancer,\n"+
      "   followed his light to the foot of the Khalkist Mountains,\n"+
      "   to the stone feet of the gods,\n"+
      "   to the crouched silence of their temple.\n"+
      "   He called down the Lancemakers, he took on\n"+
      "   their unspeakable power to crush the unspeakable evil,\n"+
      "   to thrust the coiling darkness\n"+
      "   back down the tunnel of the dragon's throat.\n");

    set_alarm(51.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Paladine, the Great God of Good,\n"+
      "   shone at the side of Huma,\n"+
      "   strengthening the lance of his strong right arm,\n"+
      "   and Huma, ablaze in a thousand moons,\n"+
      "   banished the Queen of Darkness,\n"+
      "   banished the swarm of her shrieking hosts\n"+
      "   back to the senseless kingdom of death, where their curses\n"+
      "   swooped upon nothing and nothing\n"+
      "   deep below the brightening land.\n");
    set_alarm(53.0,0.0,"command","emote softly whispers: That is all of " +
      "this enchanting song that I know.");
    set_alarm(55.0,0.0,"command","emote sheds a small tear at the beauty " +
      "of the song.");
    return "";
}

string
death_chant()
{
    set_alarm(1.0,0.0,"command","say The Death Chant of the Solamnic Knights "+
      "is sad indeed.");
    set_alarm(2.0,0.0,"command","emote plays a scale to ensure her lyre is " +
      "in tune.");
    set_alarm(5.0,0.0,"command",
      "emote sings:\n\n"+
      "   Return this man to Huma's breast:\n"+
      "   Let him be lost in sunlight,\n"+
      "   In the chorus of air where breath is translated\n"+
      "   At the sky's border receive him.\n");
    set_alarm(12.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Beyond the wild impartial skies\n"+
      "   Have you set your lodgings,\n"+
      "   In cantonment of stars, where the sword aspires\n"+
      "   In an arc of yearning, where we join in singing.\n");
    set_alarm(19.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Grant to him a warrior's rest.\n"+
      "   Above our singing, above song itself,\n"+
      "   May the ages of peace converge in a day,\n"+
      "   May he dwell in the heart of Paladine.\n");
    set_alarm(26.0,0.0,"command",
      "emote continues to sing:\n\n"+ 
      "   And set the last spark of his eyes\n"+
      "   In a fixed and holy place\n"+
      "   Above words and the borrowed land too loved\n"+
      "   As we recount the ages.\n");
    set_alarm(33.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Free from the smothering clouds of war\n"+
      "   As he once rose in infancy,\n"+
      "   The long world possible and bright before him,\n"+
      "   Lord Huma, deliver him.\n");
    set_alarm(40.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Upon the torches of the stars\n"+
      "   Was mapped the immaculate glory of childhood\n"+
      "   From that wronged and nestling country,\n"+
      "   Lord Huma, deliver him.\n");
    set_alarm(47.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Let the last surge of his breath\n"+
      "   Perpetuate wine, the attar of flowers\n"+
      "   From the vanguard of love, the last to surrender,\n"+
      "   Lord Huma, deliver him.\n");
    set_alarm(54.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Take refuge in the cradling air\n"+
      "   From the heart of the sword descending,\n"+
      "   From the weight of battle on battle\n"+
      "   Lord Huma, deliver him.\n");
    set_alarm(61.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Above the dreams of ravens where\n"+
      "   His dream first tried a rest beyond changing,\n"+
      "   From the yearning for war and the war's ending,\n"+
      "   Lord Huma, deliver him.\n");
    set_alarm(68.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Only the hawk remembers death\n"+
      "   In a late country; from the dusk,\n"+
      "   From the fade of the senses, we are thankful that you,\n"+
      "   Lord Huma, deliver him.\n");
    set_alarm(75.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Then let his shade to Huma rise\n"+
      "   Out of the body of death, of the husk unraveling\n"+
      "   From the lodging of mind upon nothing,\n"+
      "     we are thankful that you,\n"+
      "   Lord Huma, deliver him.\n");
    set_alarm(82.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Beyond the wild impartial skies\n"+
      "   Have you set your lodgings,\n"+
      "   In cantonments of stars, where the sword aspires\n"+
      "   In an arc of yearning, where we join in singing.\n");
    set_alarm(89.0,0.0,"command",
      "emote continues to sing:\n\n"+
      "   Return this man to Huma's breast\n"+
      "   Beyond the wild, impartial skies\n"+
      "   Grant to him a warrior's rest\n"+
      "   And set the last spark of his eyes\n"+
      "   Free from the smothering clouds of wars\n"+
      "   Upon the torches of the stars.\n"+
      "   Let the last surge of his breath\n"+
      "   Take refuge in the cradling air\n"+
      "   Above the dreams of ravens where\n"+
      "   Only the hawk remembers death.\n"+
      "   Then let his shade to Huma rise\n"+
      "   Beyond the wild, impartial skies.\n");
    set_alarm(99.0,0.0,"command","sigh sadly");
    set_alarm(101.0,0.0,"command","say Tis a sad day when one of the " +
      "Knighthood perishes.");
    return "";
}

equip_me()
{
    clone_object(KROBJECT + "music_lyre")->move(TO);
}

