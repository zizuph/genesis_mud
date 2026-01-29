/* created by Arman December 2018 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/clubs/warfare/defs.h"
#include <macros.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>
#include "/d/Krynn/que/newports/local.h"

inherit BASE_FILE;
inherit "/d/Krynn/common/warfare/recruit_base";
inherit "/d/Krynn/common/warfare/warfare_map";

create_newport_room()
{
    set_short("Newports recruitment office");
    set_long("You stand in a newly built wooden structure consisting " +
        "of a single room, with a large stone table to one side " +
        "covered with papers and small tokens of dark steel. Behind " +
        "the desk stands a dark-bearded human in mercenary garb, while " +
        "the walls of the room are covered in recruitment posters. Upon " +
        "the table is a small sign.\n");

    add_item(({"sign","small"}),"@@read_sign");
    add_item(({"structure","wooden structure","room","single room"}),
        "This wooden structure is a single room used for the recruitment " +
        "of willing participants for the various armies of the War of " +
        "the Lance.\n");
    add_item(({"large stone table","stone table","table"}),
        "To one side of the structure is a large stone table, roughly " +
        "carved from slate. It is covered with war reports, army " +
        "requisitions and recruitment posters. A small sign also sits " +
        "on the table that you could read.\n");
    add_item(({"papers","army requisitions","requisitions","war reports",
        "reports"}), "The large stone table is covered with army " +
        "requisitions and war reports, along with old recruitment " +
        "posters.\n");
    add_item(({"walls","wall"}), "The wooden walls are covered in " +
        "recruitment posters for the armies competing in the War of " +
        "the Lance.\n");
    add_item(({"dark-bearded human","human","mercenary","mercenary garb"}),
        "Behind the stone table stands a muscular dark-bearded human " +
        "dressed in the colours of the Langtree Mercenaries... " +
        "a local mercenary company renown for loyally following " + 
        "through with their contracts regardless of the odds or " +
        "patron. He stands ready to sign up willing participants " +
        "to the various factions competing in the War of the " +
        "Lance.\n");
    add_item(({"small tokens","tokens","dark steel","steel"}),
        "Upon the table are small tokens of dark steel - blood chits " +
        "carried by military personnel to identify the army to which " +
        "the bearer belongs.\n");
    add_item(({"posters","poster","recruitment posters",
        "recruitment poster"}), "Almost a dozen recruitment posters " +
        "cover the walls that you can examine:\n\n" +
        "    Knights of Solamnia recruitment poster,\n" +
        "    Free People of Krynn recruitment poster,\n" +
        "    Neidar Clan recruitment poster,\n" +
        "    Red Dragonarmy recruitment poster,\n" +
        "    Blue Dragonarmy recruitment poster,\n" +
        "    Black Dragonarmy recruitment poster,\n" +
        "    Green Dragonarmy recruitment poster, or\n" +
        "    White Dragonarmy recruitment poster.\n\n");

    add_cmd_item(({"posters","poster","recruitment posters",
        "recruitment poster"}), "read", "Which of the posters did " +
        "you want to read?\n\n" +
        "    Knights of Solamnia recruitment poster,\n" +
        "    Free People of Krynn recruitment poster,\n" +
        "    Neidar Clan recruitment poster,\n" +
        "    Red Dragonarmy recruitment poster,\n" +
        "    Blue Dragonarmy recruitment poster,\n" +
        "    Black Dragonarmy recruitment poster,\n" +
        "    Green Dragonarmy recruitment poster, or\n" +
        "    White Dragonarmy recruitment poster.\n\n");

    add_item(({"Knights of Solamnia recruitment poster","Knight poster",
        "Knights recruitment poster","Knight recruitment poster",
        "knights of solamnia recruitment poster","knight poster",
        "knights recruitment poster","knight recruitment poster",
        "Knights of Solamnia poster", "Knights poster",
        "knights of solamnia poster", "knights poster" }), 
        "@@read_knights_poster");
    add_cmd_item(({"Knights of Solamnia recruitment poster","Knight poster",
        "Knights recruitment poster","Knight recruitment poster",
        "knights of solamnia recruitment poster","knight poster",
        "knights recruitment poster","knight recruitment poster",
        "Knights of Solamnia poster", "Knights poster",
        "knights of solamnia poster", "knights poster" }), 
         "read", "@@read_knights_poster");

    add_item(({"free people of krynn recruitment poster","free poster",
        "free people recruitment poster", "free people poster",
        "Free People of Krynn recruitment poster","Free poster",
        "Free People recruitment poster", "Free People poster" }), 
        "@@read_free_poster");
    add_cmd_item(({"free people of krynn recruitment poster","free poster",
        "free people recruitment poster", "free people poster",
        "Free People of Krynn recruitment poster","Free poster",
        "Free People recruitment poster", "Free People poster" }), 
        "read", "@@read_free_poster");

    add_item(({"neidar clan recruitment poster","neidar poster",
        "neidar recruitment poster","clan recruitment poster",
        "clan poster", "neidar clan poster",
        "Neidar Clan recruitment poster","Neidar poster",
        "Neidar recruitment poster","Clan recruitment poster",
        "Clan poster", "Neidar Clan poster" }), "@@read_neidar_poster");
    add_cmd_item(({"neidar clan recruitment poster","neidar poster",
        "neidar recruitment poster","clan recruitment poster",
        "clan poster", "neidar clan poster",
        "Neidar Clan recruitment poster","Neidar poster",
        "Neidar recruitment poster","Clan recruitment poster",
        "Clan poster", "Neidar Clan poster" }), "read", 
        "@@read_neidar_poster");

    add_item(({"red dragonarmy recruitment poster","red poster",
        "red dragonarmy poster",
        "Red Dragonarmy recruitment poster","Red poster",
        "Red Dragonarmy poster" }), "@@read_red_poster");
    add_cmd_item(({"red dragonarmy recruitment poster","red poster",
        "red dragonarmy poster",
        "Red Dragonarmy recruitment poster","Red poster",
        "Red Dragonarmy poster" }), "read", "@@read_red_poster");

    add_item(({"blue dragonarmy recruitment poster","blue poster",
        "blue dragonarmy poster",
        "Blue Dragonarmy recruitment poster","Blue poster",
        "Blue Dragonarmy poster" }), "@@read_blue_poster");
    add_cmd_item(({"blue dragonarmy recruitment poster","blue poster",
        "blue dragonarmy poster",
        "Blue Dragonarmy recruitment poster","Blue poster",
        "Blue Dragonarmy poster" }), "read", "@@read_blue_poster");

    add_item(({"black dragonarmy recruitment poster","black poster",
        "black dragonarmy poster",
        "Black Dragonarmy recruitment poster","Black poster",
        "Black Dragonarmy poster" }), "@@read_black_poster");
    add_cmd_item(({"black dragonarmy recruitment poster","black poster",
        "black dragonarmy poster",
        "Black Dragonarmy recruitment poster","Black poster",
        "Black Dragonarmy poster" }), "read", "@@read_black_poster");

    add_item(({"green dragonarmy recruitment poster","green poster",
        "green dragonarmy poster",
        "Green Dragonarmy recruitment poster","Green poster",
        "Green Dragonarmy poster" }), "@@read_green_poster");
    add_cmd_item(({"green dragonarmy recruitment poster","green poster",
        "green dragonarmy poster",
        "Green Dragonarmy recruitment poster","Green poster",
        "Green Dragonarmy poster" }), "read", "@@read_green_poster");

    add_item(({"white dragonarmy recruitment poster","white poster",
        "white dragonarmy poster",
        "White Dragonarmy recruitment poster","White poster",
        "White Dragonarmy poster" }), "@@read_white_poster");
    add_cmd_item(({"white dragonarmy recruitment poster","white poster",
        "white dragonarmy poster",
        "White Dragonarmy recruitment poster","White poster",
        "White Dragonarmy poster" }), "read", "@@read_white_poster");

    clone_object(CLUB + "warfare_board")->move(TO, 1);

    add_cmd_item(({"sign","small"}),"read","@@read_sign");
    add_exit(TDIR + "road1","east",0,3);

}

string
read_knights_poster()
{
    say(QCTNAME(TP) + " reads one of the recruitment posters.\n");

    return "You read a recruitment poster on the wall:\n\n" +
        "    ______________________________________________________\n" +
        "    |                                                     \\' \n" +
        "    | o                                                 o |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |              LIVE AND DIE BY HONOUR                 |'\n" +
        "    |              DO WE HAVE YOUR MEASURE?               |'\n" +
        "    |                                                     |'\n" +
        "    |       Upon the plains of Solamnia the remnants      |'\n" +
        "    |       of a noble Order of knights band to face      |'\n" +
        "    |       the rising tide of darkness that threatens    |'\n" +
        "    |       to overwhelm the lands of Krynn.              |'\n" +
        "    |                                                     |'\n" +
        "    |       While blamed and reviled by the common        |'\n" +
        "    |       populace for perceived grievances stemming    |'\n" +
        "    |       from the Cataclysm hundreds of years ago,     |'\n" +
        "    |       the forces of the knighthood look to uphold   |'\n" +
        "    |       the ideals of defenders of the weak, and      |'\n" +
        "    |       the protectors of Ansalon.                    |'\n" +
        "    |                                                     |'\n" +
        "    |              'Est Sularus oth Mithas'               |'\n" +
        "    |             Their honor is their life.              |'\n" +
        "    |                                                     |'\n" +
        "    |       SEEKING:    Allies of Elnoven                 |'\n" +
        "    |                      - Calian Warriors              |'\n" +
        "    |                      - Rangers of the Westland      |'\n" +
        "    |                   Holy Order of the Stars           |'\n" +
        "    |                   Kayolin mountain dwarves          |'\n" +
        "    |                                                     |'\n" +
        "    |       TOLERATED:  Noble mercenaries                 |'\n" +
        "    |                   Kingfishers (White Robed Magi)    |'\n" +
        "    |                   Gnomish Tinkers                   |'\n" +
        "    |                                                     |'\n" +
        "    |       PROHIBITED: Goblinoids                        |'\n" +
        "    |                   Ogres                             |'\n" +
        "    |                   Magi                              |'\n" +
        "    |                   Dark Templars                     |'\n" +
        "    |                   Priests of Takhisis               |'\n" +
        "    |                                                     |'\n" +
        "    |                  A call to arms!                    |'\n" +
        "    |         <support the Knights of Solamnia>!          |'\n" +
        "    |                                                     |'\n" +
        "    |   __________________________________________________|___\n" +
        "    |  /                                                     /'\n" +
        "    \\_/_____________________________________________________/'\n" +
        "\n" +
        "\n";
}

string
read_free_poster()
{
    say(QCTNAME(TP) + " reads one of the recruitment posters.\n");

    return "You read a recruitment poster on the wall:\n\n" +
        "    ______________________________________________________\n" +
        "    |                                                     \\' \n" +
        "    | o                                                 o |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |                  WE NEED A HERO!                    |'\n" +
        "    |                                                     |'\n" +
        "    |   You had hoped that, in Solace, you would find     |'\n" +
        "    |   safe haven from the dangers of the road, but      |'\n" +
        "    |   you are startled to see goblins in armor          |'\n" +
        "    |   strutting about, looking important. These         |'\n" +
        "    |   goblins actually have the nerve to stop to        |'\n" +
        "    |   question you about a blue crystal staff! The      |'\n" +
        "    |   encounter leaves you with a bad taste in your     |'\n" +
        "    |   mouth. But this is the reality in Krynn since     |'\n" +
        "    |   the Cataclysm.                                    |'\n" +
        "    |                                                     |'\n" +
        "    |   Rumours of war in the north abound.               |'\n" +
        "    |                                                     |'\n" +
        "    |   Dragons have returned... they are not the         |'\n" +
        "    |   children's tales you thought they were.           |'\n" +
        "    |                                                     |'\n" +
        "    |   Who will step forward to defend the Free          |'\n" +
        "    |   People of Krynn? Will it be you?                  |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |   SEEKING:  All unaligned heroes and heroines       |'\n" +
        "    |                                                     |'\n" +
        "    |                  A call to arms!                    |'\n" +
        "    |         <support the Free People of Krynn>!         |'\n" +
        "    |                                                     |'\n" +
        "    |   __________________________________________________|___\n" +
        "    |  /                                                     /'\n" +
        "    \\_/_____________________________________________________/'\n" +
        "\n" +
        "\n";
}

string
read_neidar_poster()
{
    say(QCTNAME(TP) + " reads one of the recruitment posters.\n");

    return "You read a recruitment poster on the wall:\n\n" +
        "    ______________________________________________________\n" +
        "    |                                                     \\' \n" +
        "    | o                                                 o |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |               COME BACK IN GLORY                    |'\n" +
        "    |               OR ON YOUR SHIELD!                    |'\n" +
        "    |                                                     |'\n" +
        "    |       The Hill Dwarves of Krynn are a dour          |'\n" +
        "    |       and hardy clan that have little time          |'\n" +
        "    |       for the foolishness of the tall folk          |'\n" +
        "    |       that now gather their forces seeking          |'\n" +
        "    |       conquest - of lands including those           |'\n" +
        "    |       of the dwarven thanedom.                      |'\n" +
        "    |                                                     |'\n" +
        "    |       A mighty dwarven throng now gathers!          |'\n" +
        "    |       Will you join them as they seek               |'\n" +
        "    |       glory on the battlefield?                     |'\n" +
        "    |                                                     |'\n" +
        "    |       SEEKING:    Hill dwarves                      |'\n" +
        "    |                   Rockfriends                       |'\n" +
        "    |                   Shieldbearers                     |'\n" +
        "    |                                                     |'\n" +
        "    |       TOLERATED:  Mercenaries                       |'\n" +
        "    |                   Kenderkin                         |'\n" +
        "    |                   Gnomish Tinkers                   |'\n" +
        "    |                                                     |'\n" +
        "    |       PROHIBITED: Goblinoids                        |'\n" +
        "    |                   Ogres                             |'\n" +
        "    |                   Mountain dwarves                  |'\n" +
        "    |                   Baby eaters, cultists, weirdos    |'\n" +
        "    |                                                     |'\n" +
        "    |                  A call to arms!                    |'\n" +
        "    |             <support the Neidar Clan>!              |'\n" +
        "    |                                                     |'\n" +
        "    |   __________________________________________________|___\n" +
        "    |  /                                                     /'\n" +
        "    \\_/_____________________________________________________/'\n" +
        "\n" +
        "\n";
}

string
read_red_poster()
{
    say(QCTNAME(TP) + " reads one of the recruitment posters.\n");

    return "You read a recruitment poster on the wall:\n\n" +
        "    ______________________________________________________\n" +
        "    |                                                     \\' \n" +
        "    | o                                                 o |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |               BETTER RED THAN DEAD!                 |'\n" +
        "    |                                                     |'\n" +
        "    |         The Dragon Empire arises! Of the five       |'\n" +
        "    |         grand armies of Takhisis, the Red           |'\n" +
        "    |         Dragonarmy stands the most powerful.        |'\n" +
        "    |                                                     |'\n" +
        "    |         Founded by the tactical genius and self-    |'\n" +
        "    |         proclaimed Emperor of Krynn Duulket         |'\n" +
        "    |         Ariakas, this army is feared throughout     |'\n" +
        "    |         the lands as a force of oppression and      |'\n" +
        "    |         death.                                      |'\n" +
        "    |                                                     |'\n" +
        "    |         Only the victors take the spoils! Will      |'\n" +
        "    |         you choose to distinguish yourself,         |'\n" +
        "    |         and rise in the Dragon Queen's eyes to      |'\n" +
        "    |         be the best of the best?                    |'\n" +
        "    |                                                     |'\n" +
        "    |         SEEKING:    Mercenaries                     |'\n" +
        "    |                     Ogres                           |'\n" +
        "    |                     Dark Templars                   |'\n" +
        "    |                     Priests of Takhisis             |'\n" +
        "    |                     Black Robed Magi                |'\n" +
        "    |                                                     |'\n" +
        "    |         TOLERATED:  Evil goblinoids                 |'\n" +
        "    |                                                     |'\n" +
        "    |         PROHIBITED: Elves                           |'\n" +
        "    |                     Holy Order of the Stars         |'\n" +
        "    |                     Allies of Elnoven               |'\n" +
        "    |                                                     |'\n" +
        "    |                  A call to arms!                    |'\n" +
        "    |           <support the Red Dragonarmy>!             |'\n" +
        "    |                                                     |'\n" +
        "    |   __________________________________________________|___\n" +
        "    |  /                                                     /'\n" +
        "    \\_/_____________________________________________________/'\n" +
        "\n" +
        "\n";
}

string
read_blue_poster()
{
    say(QCTNAME(TP) + " reads one of the recruitment posters.\n");

    return "You read a recruitment poster on the wall:\n\n" +
        "    ______________________________________________________\n" +
        "    |                                                     \\' \n" +
        "    | o                                                 o |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |                FOR THE BLUE LADY!                   |'\n" +
        "    |                                                     |'\n" +
        "    |      Ruthless and loyal, the Blue Wing of the       |'\n" +
        "    |      Dragon Empire have cast their shadow across    |'\n" +
        "    |      the lands of Solamnia, the longtime foe of     |'\n" +
        "    |      the Dragon Queen.                              |'\n" +
        "    |                                                     |'\n" +
        "    |      Under the leadership of the charismatic        |'\n" +
        "    |      warrioress Kitiara Uth Matar, and with         |'\n" +
        "    |      the support of the undead minions of the       |'\n" +
        "    |      Death Knight Lord Soth, the Blue Dragonarmy    |'\n" +
        "    |      is peerless in its victories in the northern   |'\n" +
        "    |      lands.                                         |'\n" +
        "    |                                                     |'\n" +
        "    |         SEEKING:    Mercenaries                     |'\n" +
        "    |                     Undead minion                   |'\n" +
        "    |                     Ogres                           |'\n" +
        "    |                     Dark Templars                   |'\n" +
        "    |                     Priests of Takhisis             |'\n" +
        "    |                     Black Robed Magi                |'\n" +
        "    |                                                     |'\n" +
        "    |         TOLERATED:  Evil goblinoids                 |'\n" +
        "    |                                                     |'\n" +
        "    |         PROHIBITED: Holy Order of the Stars         |'\n" +
        "    |                     Allies of Elnoven               |'\n" +
        "    |                                                     |'\n" +
        "    |                  A call to arms!                    |'\n" +
        "    |           <support the Blue Dragonarmy>!            |'\n" +
        "    |                                                     |'\n" +
        "    |   __________________________________________________|___\n" +
        "    |  /                                                     /'\n" +
        "    \\_/_____________________________________________________/'\n" +
        "\n" +
        "\n";
}

string
read_black_poster()
{
    say(QCTNAME(TP) + " reads one of the recruitment posters.\n");

    return "You read a recruitment poster on the wall:\n\n" +
        "    ______________________________________________________\n" +
        "    |                                                     \\' \n" +
        "    | o                                                 o |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |                 FROM THE SHADOWS                    |'\n" +
        "    |                 SILENT -- DEADLY                    |'\n" +
        "    |                                                     |'\n" +
        "    |        The Black Dragonarmy holds control of        |'\n" +
        "    |        the east of Ansalon in the name of the       |'\n" +
        "    |        Dragon Empire, through both ruthless         |'\n" +
        "    |        force and through alliance with the          |'\n" +
        "    |        minotaurs of the Blood Sea Isles.            |'\n" +
        "    |                                                     |'\n" +
        "    |        Under the leadership of the half-ogre        |'\n" +
        "    |        Lucien of Takar, the Black Dragonarmy        |'\n" +
        "    |        now seeks to raise its profile in the        |'\n" +
        "    |        eyes of the Dragon Queen, and stake a        |'\n" +
        "    |        claim as the dominant Dragonarmy on the      |'\n" +
        "    |        battlefields of Solamnia and Abanasinia!     |'\n" +
        "    |                                                     |'\n" +
        "    |         SEEKING:    Mercenaries                     |'\n" +
        "    |                     Minotaurs                       |'\n" +
        "    |                     Bloodsea Pirates                |'\n" +
        "    |                     Ogres                           |'\n" +
        "    |                     Dark Templars                   |'\n" +
        "    |                     Priests of Takhisis             |'\n" +
        "    |                     Black Robed Magi                |'\n" +
        "    |                                                     |'\n" +
        "    |         TOLERATED:  Evil goblinoids                 |'\n" +
        "    |                                                     |'\n" +
        "    |         PROHIBITED: Holy Order of the Stars         |'\n" +
        "    |                     Allies of Elnoven               |'\n" +
        "    |                                                     |'\n" +
        "    |                  A call to arms!                    |'\n" +
        "    |          <support the Black Dragonarmy>!            |'\n" +
        "    |                                                     |'\n" +
        "    |   __________________________________________________|___\n" +
        "    |  /                                                     /'\n" +
        "    \\_/_____________________________________________________/'\n" +
        "\n" +
        "\n";
}

string
read_green_poster()
{
    say(QCTNAME(TP) + " reads one of the recruitment posters.\n");

    return "You read a recruitment poster on the wall:\n\n" +
        "    ______________________________________________________\n" +
        "    |                                                     \\' \n" +
        "    | o                                                 o |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |               BE YOUR ENEMIES' WORST                |'\n" +
        "    |                     NIGHTMARE!                      |'\n" +
        "    |                                                     |'\n" +
        "    |                JOIN THE GREEN WING!                 |'\n" +
        "    |                                                     |'\n" +
        "    |         Overseeing the campaign against the         |'\n" +
        "    |         elven Kingdom of Silvanesti, the            |'\n" +
        "    |         Green Wing of the Dragon Empire excels      |'\n" +
        "    |         at protracted guerilla campaigns,           |'\n" +
        "    |         using a mix of terrorist methods and        |'\n" +
        "    |         psychological intimidation tactics.         |'\n" +
        "    |         This has earnt it a well-deserved           |'\n" +
        "    |         infamy, a reputation the Green Dragon       |'\n" +
        "    |         Highlord Salah-Khan wishes to extend        |'\n" +
        "    |         to the rest of Krynn!                       |'\n" +
        "    |                                                     |'\n" +
        "    |         SEEKING:    Mercenaries                     |'\n" +
        "    |                     Assassins and rogues            |'\n" +
        "    |                     Ogres                           |'\n" +
        "    |                     Dark Templars                   |'\n" +
        "    |                     Priests of Takhisis             |'\n" +
        "    |                     Black Robed Magi                |'\n" +
        "    |                                                     |'\n" +
        "    |         TOLERATED:  Evil goblinoids                 |'\n" +
        "    |                                                     |'\n" +
        "    |         PROHIBITED: Holy Order of the Stars         |'\n" +
        "    |                     Allies of Elnoven               |'\n" +
        "    |                                                     |'\n" +
        "    |                  A call to arms!                    |'\n" +
        "    |          <support the Green Dragonarmy>!            |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |   __________________________________________________|___\n" +
        "    |  /                                                     /'\n" +
        "    \\_/_____________________________________________________/'\n" +
        "\n" +
        "\n";
}

string
read_white_poster()
{
    say(QCTNAME(TP) + " reads one of the recruitment posters.\n");

    return "You read a recruitment poster on the wall:\n\n" +
        "    ______________________________________________________\n" +
        "    |                                                     \\' \n" +
        "    | o                                                 o |'\n" +
        "    |                                                     |'\n" +
        "    |                                                     |'\n" +
        "    |                FROM ICEREACH COMES                  |'\n" +
        "    |                DEATH ON WHITE WINGS!                |'\n" +
        "    |                                                     |'\n" +
        "    |         Far to the south in the frozen lands        |'\n" +
        "    |         of Icereach the White Wing of the           |'\n" +
        "    |         Dragon Empire plot for greater things       |'\n" +
        "    |         than the domination of Ice Folk and         |'\n" +
        "    |         Walrus Men.                                 |'\n" +
        "    |                                                     |'\n" +
        "    |         The dark elf Highlord Feal-Thas             |'\n" +
        "    |         secretly formulates plans to expand         |'\n" +
        "    |         his operations beyond Icewall Castle        |'\n" +
        "    |         and become a more dominant player in        |'\n" +
        "    |         the eyes of the Dragon Queen!               |'\n" +
        "    |                                                     |'\n" +
        "    |         Bereft of leadership amongst his            |'\n" +
        "    |         troops, Fael-Thas now seeks for             |'\n" +
        "    |         highmasters to drive his conquests          |'\n" +
        "    |         and bring Winter to the lands of the        |'\n" +
        "    |         north!                                      |'\n" +
        "    |                                                     |'\n" +
        "    |         SEEKING:    Mercenaries                     |'\n" +
        "    |                     Minotaurs                       |'\n" +
        "    |                     Thanoi                          |'\n" +
        "    |                     Ogres                           |'\n" +
        "    |                     Dark Templars                   |'\n" +
        "    |                     Priests of Takhisis             |'\n" +
        "    |                     Black Robed Magi                |'\n" +
        "    |                                                     |'\n" +
        "    |         TOLERATED:  Evil goblinoids                 |'\n" +
        "    |                                                     |'\n" +
        "    |         PROHIBITED: Holy Order of the Stars         |'\n" +
        "    |                     Allies of Elnoven               |'\n" +
        "    |                                                     |'\n" +
        "    |                  A call to arms!                    |'\n" +
        "    |           <support the White Dragonarmy>!           |'\n" +
        "    |                                                     |'\n" +
        "    |   __________________________________________________|___\n" +
        "    |  /                                                     /'\n" +
        "    \\_/_____________________________________________________/'\n" +
        "\n" +
        "\n";
}

string
read_sign()
{
    say(QCTNAME(TP) + " reads the small sign on the desk.\n");

    return "You read the small sign on the desk:\n\n" +
        "   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" +
        "   @@==                                         ==@@\n" +
        "   @@== LANGTREE MERCENARIES RECRUITMENT OFFICE ==@@\n" +
        "   @@==                                         ==@@\n" +
        "   @@== 'Faithfully serving the highest bidder  ==@@\n" +
        "   @@==  since the Cataclysm!'                  ==@@\n"+
        "   @@==                                         ==@@\n" +
        "   @@==  Eager to join the War of the Lance     ==@@\n" +
        "   @@==  for glory, blood, or spoils? Here you  ==@@\n" +
        "   @@==  can <support> one of the warring       ==@@\n" +
        "   @@==  factions, or <replace> a lost chit     ==@@\n" +
        "   @@==  identifying your support of a faction. ==@@\n" +
        "   @@==                                         ==@@\n" +
        "   @@==  Read the recruitment posters to find   ==@@\n" +
        "   @@==  out more!                              ==@@\n" +
        "   @@==                                         ==@@\n" +
        "   @@==  Participants in the war can also       ==@@\n" +
        "   @@==  <wcheck> [army] or <warcheck> [army]   ==@@\n" +
        "   @@==  for details on troop disposition on    ==@@\n" +
        "   @@==  the battlefields!                      ==@@\n" +
        "   @@==                                         ==@@\n" +
        "   @@==            - the Mad Baron of Langtree  ==@@\n" +
        "   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" +
        "\n";
}

void
init()
{
    ::init();
    ADA("support");
    ADA("desert");
    ADA("replace");
    ADA("wcheck");
    add_action("wcheck", "warcheck");
}

int
wcheck(string str)
{
    int i, k;
    string *areas;
    string str2;

    NF("You need to be participating in the War of the Lance to " +
        "check the warring armies here!\n");
    if(!IS_CLUB_MEMBER(TP))
        return 0;

    NF("That isn't an eligible warfare army to check.\n");
    if(!CLUB_MANAGER->query_is_warfare_army(str))
	return 0;

    str = CLUB_MANAGER->query_warfare_army_string(str);
    str2 = CLUB_MANAGER->convert_warfare_army_name(str);
    areas = ARMYMASTER->query_areas_of_army(str);    
    k = sizeof(areas);

    if (!k)
    {
	notify_fail("The " + str2 + " does not control any areas!\n");
	return 0;
    }

    write("The " + str2 + " are currently controlling " + LANG_WNUM(k) +
	(k > 1 ? " areas" : " area") + ".\n");
   
    i = -1;

    while (++i < k)
    {
	write(area_info(areas[i]));
    }
    return 1;
}

int
support(string str)
{
    string army, army_name;

    NF("Support which army?\n");
    if (!str)
	return 0;

    parse_command(str, TO, "[the] %s", army);

    army = CLUB_MANAGER->query_warfare_army_string(army);

    NF("That isn't an eligible warfare army to support.\n");
    if(!CLUB_MANAGER->query_is_warfare_army(army))
	return 0;

    NF("You currently support the " +CLUB_MANAGER->query_warfare_army(TP)+
        "! You will need to <desert> them first to support a different " +
        "army!\n");
    if(IS_CLUB_MEMBER(TP))
        return 0;

    army_name = CLUB_MANAGER->convert_warfare_army_name(army);

    if(!CLUB_MANAGER->query_valid_warfare_army(TP, army))
    {
        say("The muscular dark-bearded human behind the table " +
            "looks at " +QTNAME(TP)+ " quizzically and says: " +
            "The " +army_name+ " do not want the support of someone " +
            "like you.\n");
        notify_fail("The muscular dark-bearded human behind the " +
            "table looks at you quizzically and says: The " +army_name+
            " do not want the support of someone like you.\n");
        return 0;
    }
    
    CLUB_MANAGER->add_member(TP);
    CLUB_MANAGER->set_warfare_army(TP, army);
    CLUB_MANAGER->add_krynn_war_player_stats(TP, army, 0, 0);

    object club_obj = clone_object(WAR_OBJ);
    club_obj->move(TP, 1);

    tell_room(E(TP), QCTNAME(TP) + " has entered the battle for control " +
        "of Ansalon on the side of the " +
        CLUB_MANAGER->query_warfare_army_name(TP)+ "!\n", TP);
    tell_object(TP,"You have entered the battle for control of Ansalon " +
        "on the side of the " +CLUB_MANAGER->query_warfare_army_name(TP)+
        "!\n\nThe muscular dark-bearded human behind the table hands " +
        "you a dark steel blood chit identifying you as supporting " +
        CLUB_MANAGER->query_warfare_army_name(TP)+ ".\n");
    return 1;

}

int
desert(string str)
{
    string army;

    NF("Desert whom?\n");
    if (!str)
	return 0;

    parse_command(str, TO, "[the] %s", army);

    NF("You are not currently supporting any army, so can't desert " +
        "anyone!\n");
    if(!IS_CLUB_MEMBER(TP))
        return 0;

    army = CLUB_MANAGER->query_warfare_army_string(army);

    NF("If you want to desert, type <desert the " +
        CLUB_MANAGER->query_warfare_army(TP)+ ">.\n");
    if (army != lower_case(CLUB_MANAGER->query_warfare_army(TP)))
	return 0;

    tell_object(TP,"You have deserted the " +
        CLUB_MANAGER->query_warfare_army(TP)+ " and are no longer " +
        "participating in the war for Krynn!\n");

    CLUB_MANAGER->remove_member(TP);
    CLUB_MANAGER->remove_warfare_army(TP);
    CLUB_MANAGER->add_krynn_war_player_stats(TP, army, 0, 0);

    return 1;
}

int
replace(string str)
{
    object club_object = present("_warfare_club_object_", TP);

    NF("Replace what? Your war chit?\n");
    if (!str)
	return 0;

    NF("Replace your war chit?\n");
    if ((str != "war chit") && (str != "chit") && (str != "my war chit"))
        return 0;

    NF("You haven't supported an army yet! You can't get a chit until " +
        "you have done so!\n");
    if(!IS_CLUB_MEMBER(TP))
        return 0;

    NF("You haven't lost your war chit! No need to replace it.\n");
    if (objectp(club_object))
        return 0;
  
    tell_room(E(TP), QCTNAME(TP) + " gets a replacement war chit.\n", TP);
    tell_object(TP, "You get yourself a replacement war chit.\n");

    setuid();
    seteuid(getuid());

    object chit_obj = clone_object(WAR_OBJ);
    chit_obj->move(TP, 1);

    return 1;

}
