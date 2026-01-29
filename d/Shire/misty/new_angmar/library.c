/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <stdproperties.h>

void create_shire_room()
{
    set_short("library room");
    set_long("This once grand room has been plundered and destroyed " +
        "almost beyond recognition. The shelves have been broken and " +
        "lie on the ground in heaps of splintered wood. The books, " +
        "tomes, parchments and scrolls that were once housed on the " +
        "shelves have been destroyed or carried off. Rubble covers " +
        "the ground. Amazingly enough, some books, parchments, and " +
        "scrolls survived. They are sticking out of the rubble.\n");

    add_item(({"scroll", "scrolls"}),
        "The scrolls are made of wrapped paper. They are buried in " +
        "the rubble and have survived the rampant destruction. It " +
        "looks like the largest one can be read.\n");
    add_cmd_item(({"scroll", "large scroll"}),  "read", "@@read_l_scroll@@");

    add_item(({"parchment", "parchments"}),
        "Ripped and torn, the parchments lie half buried in the dirt " +
        "and rubble. They are torn pretty badly. However, there looks like " +
        "there are some that can be read.\n");
    add_cmd_item(({"first parchment", "1st parchment"}),  "read", "@@read_parchment1@@");
    add_cmd_item(({"second parchment", "2nd parchment"}),  "read", "@@read_parchment2@@");

    add_item(({"books", "book"}),
        "Many books are torn, burned, and shredded with their pages " +
        "scattered about the room. One ripped page lies on top of the " +
        "rubble, and looks like it can be read.\n");
    add_cmd_item(({"book", "ripped page", "page"}),  "read", "@@read_book@@");
    
    
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
       
    add_exit(NEW_ANGMAR + "vote", "west");
    
}



string
read_l_scroll()
{
    return "On the scroll you read the following:\n\n"+
    "WOT ME DOODED TERDAY!\n"+
    "scribbled by Nogg\n"+
    "diz iz rote by Nogg vutgob of da ARMY!\n\n"+
 
    "me woked up inna barikz terday but wot wot wot? der wuz no udder " +
    "zoljerz kud me finded!! wot lil vutgob ta do? oiz no ken killim " +
    "ded big big elvzez onna me ownzez!\n\n"+
 
    "but duh! der wuz glub fur me inna dwoprum! anna zeel too! ha ha " +
    "ha got stuff go killim obbitzez YEAH!! killim an EETem taz gud " +
    "gud!! yum!!\n\n"+
 
    "den me gode bree an der obbit lans an killim dedded sum obbitz! " +
    "but den alla obbitz run run ide go way no cud fine nur ta eet! " +
    "wot oiz gunna do eh?\n\n"+

    "den me goze onna bote ter da plaz wer da nitzeyz liv! big big " +
    "kazzel callim Wigugud kip! gottim biiiiiig wal roun it an lot " +
    "lot nitz in dere!!\n\n"+
 
    "ha ha boogerz ta nitz me finkded!\n\n"+
 
    "denz me gode ter da zollaz wiluge, dez lil GELZ an stoopid OOMINZ " +
    "dere killim go smash!! SMASH!! dedded em reel kwik! but oiz wuz " +
    "eeted alla dem obbitz, kudden eet no nuffin! wot me do, no wanna "+
    "let all gud gud pulp go ter waze!\n\n"+
 
    "git pulp! snik shhhhhh reel sneeky inna da plaz wer nitzez liv! " +
    "drop pulp an run run run heh outta gen! den doit aggen! an aggen! " +
    "an aggen!!!!\n\n"+
 
    "me kumdded bak wiv pulp an deze aaall dese nitz goin bonkers!!! " +
    "HAW HAW!!! but me snik!! uh oh! gotta crap! iz orrite, juz crap " +
    "inna da kip! heheheheheheh! an drop nuvver pulp too! 'stop yew " +
    "bad gobby!!' sed dem nitz! freakin nitz go wee wee inna dere armurz " +
    "ha ha!\n\n"+
 
    "dat wuz day dat me vutgob did go da plaz wer da nitz liv! oiz " +
    "fink me go dere gen! yew kum wit, eh?\n\n";
}


string
read_parchment1()
{
    return "On the parchment you read:\n\n"+
    "wen me tuwned t'hedgehog\n"+
    "scored by Necros\n"+
    "me hedgehog\n\n"+

    "me wuz walkin aroun in da landz of gondow wen me\n"+
    "get da fun idee t'SMASH da ztoopid guawdz of\n"+
    "Minaz Tivvif. me nokk at da ztoopid gait wiz me\n"+
    "luvly klub (me marri me klub if me kud). Da\n"+
    "guawdz ztawtz wunning awound laik chikkenz in\n"+
    "a kaig. me zmail gleefully. zuddenly da gait\n"+
    "openz up and many guawdz wun out t'attack me!\n"+
    "me wedy wiz me klub. me ztart SMASH. dey fall\n"+
    "laik gwainz in da wind!\n"+
    "me feel pain!\n"+
    "me feel mowe pain!\n"+
    "me look laik hedgehog!\n"+
    "da kowawdz on da wall zhootz awwowz at me.\n"+
    "me huwt.\n"+
    "me angwi.\n"+
    "me twi t'hit da ztoopid kowawdz wiz me klub.\n"+
    "dey too hi up.\n"+
    "me twi t'skail da wall wiz me klub.\n"+
    "me get pain in me awmz.\n"+
    "me haz t'leeve.\n"+
    "me fuwiouz.\n"+
    "me SMASH all da wangewz n'wohimz me zee on da\n"+
    "wai t'hedquawtewz. dei will not help gondow wen\n"+
    "da taim cumz. wen me cum t'da quawtewz, me go\n"+
    "t'da pub. me dwain me sowwowz and dwag da awwowz\n"+
    "out of me hawd zkin.\n"+
    "me tink next taim me will get em.\n"+
    "me will twi 'til me SMASH em all.\n"+
    "no awwowz wil ztop me fow long.\n"+
    "at leezt me now now wat me alwaiz fogt:\n"+
    "GONDOWIANZ AW WIMPZ!!\n\n"+

    "nekwoz da zawgent of da awmi of angmaw.\n\n";
}


string
read_book()
{
    return "On the page you read:\n"+
    "Hobbopulp\n"+
    "drawn by Raffe\n"+
    "The book about Hobbopulp.\n\n"+

    "It was a nice lagfree day, when the Great Raffe was walking throw " +
    "Shire.\n"+
    
    "Poor Raffe had no money for the stupied boat...Raffe pulped a " +
    "hobbit(npc)..\n"+
    
    "That was very stupied...Because the extremily dangerous Sticker " +
    "the greenhorne hobbit saw me...\n"+
    
    "I almost cried when hhreatend me, I was so scared..Me think VERY " +
    "stupied hobbit.\n"+

    "Me think make hobbopulp of him..but then Rangar, Hettar and a " +
    "wheathered brown-beard human arrived..Poor gobo brain couldnt " +
    "figure it out that they would kick my green gobo butt. Then one " +
    "or two more humans arrived...me think AHHH me kill many today!!! :)\n"+

    "BUT..I only got one...me bad armour...I had to run to my home.....\n"+

    "Then i got back to kill  them they where gone...\n"+

    "Me hunt now..HEHEHE they can run but they cant hide!!!\n"+

    "'BE COUNTIENED!\n"+

    "End of part one..\n\n";
}

string read_parchment2()
{
    return "On the parchment you read:\n\n\n"+
    "The Glorious Army of Angmar:\n" +
    "                         Captain of the Army of Angmar\n"+
"                                    Denethor\n"+
"\n"+
"                                  Lieutenants\n"+
"                        Jakle, Gector, Reficul, Skulker\n"+
"\n"+
"                                Warrant Officers\n"+
"                  Hawk, Smokey, Carpus, Newton, Ulath, Lazarus\n"+
"\n"+
"                                   Sergeants\n"+
"                     Javert, Krangh, Manowar, Emper, Morg,\n"+
"                    Bloodlust, Vlady, Karpath, Ragul, Bogart\n"+
"\n"+
"                                   Corporals\n"+
"Bildor, Aaz, Per, Hendrix, Astra, Locklear, Dethraine, Deproelius, Morti,\n"+
"Dazalarian, Talbot, Nanja, Flingbang, Jar, Stryder\n"+
"\n"+
"                                Standard Bearers\n"+
"Hades, Purple, Mickey, Maren, Twolf, Nixon, Talis, Frajola, Geb, Chmee,\n"+
"Elliot, Vgi, Mortimor, Fidi, Radha, Rhunt, Stern, Funky, Kayt, Zeus,\n"+
"Janice, Dolmarth, Halb, Ugelplect, Kysler\n"+
"\n"+
"                                    Footmen\n"+
"Uriel, Java, Sartan, Hoax, Doughboy, Eleron, Gozer, Lubu, Daryoon,\n"+
"Drakman, Mantis, Gnarf, Caldin, Elysia, Zeppelin, Duh, Bebop, Moridin,\n"+
"Tinkel, Sin, Metallica, Pippilotta, Laurel, Pirvan, Thurin, Cabral,\n"+
"Bueradin, Tovos, Bloodfang, Cerlion, Fzoul, Mars, Ishnacht, Catherine,\n"+
"Oloth, Avathar, Gallahan, Guard, Dunhough, Morncki, Gram, Spider, Tweed,\n"+
"Holiday, Lynxx, Gruff, Bign, Gargayle, Skarsnik, Dundurs, Whisper, Ghazg,\n"+
"Khali, Woj\n\n";

}
