/* Stralle @ Genesis 010708
 *
 * A wandering npc to ask about pilgrimage
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/pot/guild.h"
#include "/d/Ansalon/guild/pot/spells.h"
#include "npc.h"
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/d/Ansalon/guild/pot/obj/living/npc";
inherit AUTO_TEAM

mapping gWannabees = ([ ]);

void arm_me();

string
query_guild_title_race()
{
    return "Kilthjem";
}

int
query_guild_family_name()
{
    return 1;
}

void
restore_vars()
{
    setuid();
    seteuid(getuid());
    
    gWannabees = restore_map(MASTER);
}

void
save_vars()
{
    setuid();
    seteuid(getuid());
    
    save_map(gWannabees, MASTER);
}

void
create_pot_monster()
{
    if(!IS_CLONE)
        return;

    set_pick_up_team(({"_templeguard_"}));

    set_name("fallorn");
    set_living_name("fallorn");
    set_introduce(1);
    add_name("priest");

    set_race_name("half-elf");
    set_adj(({"lean", "pale"}));
    
/*    set_long("This crooked, shabby old human is despite the outward " +
    "appearance a powerful Priest of Takhisis. From behind the cowl " +
    "of his old dirty robe, he studies you with cunning. He is here " +
    "to help those that need guidance, and have questions to ask.\n");
*/
    add_prop(CONT_I_HEIGHT, 172);
    add_prop(CONT_I_WEIGHT, 55000);

    set_stats(({ 90, 130, 110, 160, 160, 110 }));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB,          70);
    set_skill(SS_DEFENCE,           75);
    set_skill(SS_PARRY,             70);
    set_skill(SS_AWARENESS,         65);
    set_skill(SS_SPELLCRAFT,        65);
    set_skill(SS_ELEMENT_LIFE,      65);
    set_skill(SS_ELEMENT_AIR,       65);
    set_skill(SS_FORM_DIVINATION,   65);
    set_skill(SS_FORM_ENCHANTMENT,  60);
    set_skill(SS_FORM_ABJURATION,   60);

    set_skill(PS_GUILD_LEVEL, 49);
    set_skill(PS_SPELLS, PALIGN_ID | PTELL_ID);

    set_all_hitloc_unarmed(10);

    set_alignment(-850);
    set_knight_prestige(850);

    set_act_time(13 + random(7));
    add_act("emote mutters a short prayer to the Queen of Darkness.");
    add_act("say In the dungeons of Her temple, many a pilgrim with " +
        "false intentions now pay for their foolishness.");
    add_act("say If yer goal be to serve our Queen such as I, " +
        "happen it might I would have advice for ye.");
    add_act("say I may have answers ye seek.");
    add_act("say Seek ye the temple, beware if ye be not priest or " +
        "soldier under Her command, lest ye are on a pilgrimage.");

    set_cact_time(5);
    add_cact("say I curse ye!");
    add_cact("sneer");
    add_cact("say The hatred of the Queen of Darkness will follow you to yer grave!");

    set_default_answer(QCTNAME(TO) + " mutters: Spake I of that, in the " +
        "Abyss I would suffer for eternity.\n");

    add_ask(" [for] 'help' / 'answers' ", "say Ye be seeking answers? " +
        "Then pilgrimage ye should first seek.", 1);
    add_ask(" [the] 'dungeons' ", "say Her dungeons are deep and endless " +
        "with plenty of room still left.", 1);
    add_ask(" [the] [dark] 'queen' ", "say Our Queen and protector. She " +
        "of many faces is the reason ye see all that be around ye.", 1);
    add_ask(" [the] [dark] 'temple' ", "say Into Her temple ye may enter, " +
        "be ye priest or soldier under Her command or being on a " +
        "pilgrimage.", 1);
    add_ask(" 'goal' / 'serve' / 'priests' / 'priesthood' / 'guild' ",
        "say Seek ye priesthood, seek first pilgrimage.", 1);
    add_ask(" [about] 'pilgrims' / 'pilgrimage' ",
        VBFC_ME("answer_pilgrimage"));
    add_ask(" [about] 'advice' ", VBFC_ME("answer_advice"));
    add_ask(" [to] 'jot' / 'report' [down] [my] [name] [daily] [report] ",
        VBFC_ME("answer_report"));

    restore_vars();
}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}

void
arm_me()
{
    setuid();
    seteuid(getuid());

    clone_object(NWEP + "mace")->move(this_object(), 1);
    clone_object(NARM + "black_chain_shirt")->move(this_object(), 1);
    clone_object(GUILDDIR + "obj/clerical_robe")->move(this_object(), 1);
    clone_object(GUILDDIR + "obj/sandals")->move(this_object(), 1);

    command("wear all");
    command("wield all");

    ::arm_me();
}

varargs string
answer_pilgrimage(int round = 0)
{
    switch (round)
    {
        case 0:
            set_busy(B_SPEAKING);
            command("say Seek ye to marvel at the beauty of Her temple " +
                "and pray at Her altar, yer journey has but begun.");
            break;
        case 1:
            command("say To do so ye required are, to be a pilgrim, if " +
                "not already priest or soldier under Her command.");
            break;
        case 2:
            command("say Heed me warning though for be yer intentions " +
                "false, Her endless dungeons still offer accommodations.");
            break;
        case 3:
            command("say The course of two weeks be that of a normal " +
                "pilgrimage.");
            break;
        case 4:
            command("say For the truly faithful that period can be " +
                "extended.");
            break;
        case 5:
            command("say I be just a scribe, forwarding me notes to " +
                "the very council of High Priests.");
            break;
        case 6:
            command("say Me sure you see we cannot let just anyone " +
                "into Her temple.");
            break;
        case 7:
            command("say Should ye wish me to jot down yer name in " +
                "me daily report, just ask me to do so.");
            unset_busy(B_SPEAKING);
            break;
    }

    if (round < 7)
        set_alarm(3.0, 0.0, &answer_pilgrimage(round + 1));
    return "";
}

string
answer_advice()
{
    command("say " + ({ "The priests are harsh.", "Becoming a priest " +
        "requires yer complete and utter dedication.", "Only priests, " +
        "soldiers and pilgrims be allowed to enter Her temple.",
        "Pilgrims usually bring gifts to Her temple.", "Pilgrims pray " +
        "to the Dark Queen in Her temple.", "A normal pilgrimage takes " +
        "two weeks.", "Pilgrims whose goal it is to serve as priest, " +
        "extend their pilgrimage by four weeks." })[random(7)]);
    return "";
}

string
answer_report()
{
    string *arr;
    int x, size;
                
    if (!query_met_living(this_player()->query_real_name()))
    {
        command("say to " + OB_NAME(this_player()) + " I would need " +
            "yer name first.");
        return "";
    }

    if (pointerp(gWannabees[this_player()->query_real_name()]))
    {
        command("say to " + OB_NAME(this_player()) + " Yer name is " +
            "already in me report.");
        return "";
    }
    
    if (member_array(this_player()->query_real_name(),
        GUILD_ADMIN->query_guild_council()) >= 0)
    {
        /* whisper to the player those names and short descriptions he
         * has recieved from would-be pilgrims as well as their aura
         * from pbless
         */

        command("say to " + OB_NAME(this_player()) + " Aye, a report " +
            "ye shall have.");
        if (!m_sizeof(gWannabees))
        {
            command("whisper to " + OB_NAME(this_player()) + " None has " +
                "come by since yer last visit and declared themselves " +
                "willing pilgrims.");
        }
        else
        {
            command("whisper to " + OB_NAME(this_player()) + " I have " +
                "the following names in me report;");
            for (x = 0, arr = m_indices(gWannabees), size = sizeof(arr) ;
                x < size ; x++)
            {
                command("whisper to " + OB_NAME(this_player()) + " " +
                    capitalize(arr[x]) + ", " +
                    LANG_ADDART(gWannabees[arr[x]][0]) + " whom I sensed " +
                    LANG_ADDART(gWannabees[arr[x]][1]) + " aura about.");
            }
            command("whisper to " + OB_NAME(this_player()) + " That " +
                "concludes me report and I shall at once begin another.");

            gWannabees = ([ ]);
            save_vars();
        }
    }
    else if (this_player()->query_guild_name_occ() == GUILD_NAME)
    {
        /* Peer curiously */
        command("say to " + OB_NAME(this_player()) + " But ye already " +
            "serve our Queen, tell I can.");
        command("peer " + OB_NAME(this_player()));
    }
    else if (this_player()->query_guild_name_occ() == "Dragonarmy")
    {
        command("say to " + OB_NAME(this_player()) + " But ye already " +
            "serve our Queen, tell I can.");
        command("say to " + OB_NAME(this_player()) + " Might that ye " +
            "want te serve in another way. I shall make a note of that.");
        command("cast palign " + OB_NAME(this_player()));
        set_busy(B_WAITING);
    }
    else if (GUILD_ADMIN->query_pilgrim(this_player()->query_real_name()))
    {
        command("say to " + OB_NAME(this_player()) + " But ye already " +
            "be pilgrim.");
        command("peer " + OB_NAME(this_player()));
    }
    else
    {
        command("say to " + OB_NAME(this_player()) + " So ye wish " +
            "me to jot down yer name in my report. So be it.");
        command("cast palign " + OB_NAME(this_player()));
        set_busy(B_WAITING);
        /* Cast palign, jot down the name and short description and
         * the findings from the spell.
         */
    }
    
    return "";
}
    
void
cast_palign_hook(string s, object tar)
{
    if (environment(tar) != environment(TO))
    {
        command("shrug");
        unset_busy(B_WAITING);
        return;
    }

    switch (s)
    {
        case "midnight black":
        case "black":
        case "dark grey":
            command("say to " + OB_NAME(tar) + " Yer soul is awaiting " +
                "Her coming. Good.");
            command("emote scribbles something in his papers.");
            command("say to " + OB_NAME(tar) + " Yer name is now in " +
                "me report.");
            break;
        case "grey":
            command("say to " + OB_NAME(tar) + " Neraka could be a " +
                "dangerous place for creatures such as you.");
            command("emote scribbles something in his papers.");
            break;
        default:
            command("say to " + OB_NAME(tar) + " And what would ye " +
                "be doing as a pilgrim!? A spy I say ye are!");
            command("emote scribbles something in his papers.");
            break;
    }

    gWannabees[tar->query_real_name()] = ({ tar->query_nonmet_name(), s });
    save_vars();
    unset_busy(B_WAITING);
}
