/* Entrance to guild hall */
// creator(s):   Nick, Percy
// last update:  Teth  09 Jan 97
// update:  Louie 28 Aug 2005 - Allow Shieldbearers lay to join.
//          Addendum - Allow Archers and Gardeners to join
// purpose:      The Knight joining room
// note:         New joining sequence added, line 463
// bug(s):
// to-do:

/* Include */
#include "../../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <filter_funs.h>

inherit IN_BASE;

#define SAVE_FILE             VLOG + "joinroom"

/* Prototypes */

int add_member(object player, string type, string sponsor);
int check_join(object player);
int join_us(object player, string type);
void write_debug(string str);

/* Global variables */

static mapping positions = ([ ]);
string str1, str2, whom, kname, sname;
int    here, step, ceremony_id = 0;
object gOrdheus;

/* Functions */

void
reset_vin_room()
{
    if (!present("gOrdheus", TO))
    {
        gOrdheus = clone_object(VNPC + "ordheus");
        gOrdheus->move(TO);
    }
}

void
create_vin_room()
{
    set_short("Entrance");
    set_long("This small chamber is the entrance to the Solamnian guild. " +
      "It is also where the joining and leaving ceremonies for the " +
      "Knights of Solamnia guild occurs. A podium sits in one corner " +
      "of the chamber. A plaque is attached to the front of the " +
      "podium. To the west is a small den where potential members " +
      "may post about their wishes to join the guild. The inner " +
      "courtyard lies to the south, while a great hall can be seen " +
      "to the north. A small banner is attached off to the side " +
      "on the east wall, away from the entrance to the library.\n");

    AI(({"chamber","small chamber"}),"You're in it. Have a look around.\n");
    AI(({"floor","ceiling","wall"}),"It is made of the same sturdy stone " +
      "as the rest of Vingaard Keep.\n");
    AI("walls","They are made of the same sturdy stone as the rest of " +
      "Vingaard Keep.\n");
    AI(({"stone","sturdy stone"}),"It is dark and volcanic in origin.\n");
    AI("podium","On the tall podium rests a thick book, most likely " +
      "on the topic of this guild.\n");
    AI(({"book", "guild book", "thick book"}),
      "This is the book containing information, history, and rules on "+
      "the Solamnian Knights Guild. To read the information " +
      "within, you can read <pagenumber>, and it would be best " +
      "to start with page one, of course.\n");
    ACI(({"book","guild book","thick book"}),"get","The book is attached " +
      "to the podium, with its spine embedded in the wood. You can't " +
      "get it.\n");
    AI("spine","It is embedded in the wood of the podium.\n");
    AI("plaque","The plaque is made of gold, with embossings.\n");
    ACI(({"plaque","embossings"}),"read","The plaque reads:\n" +
      "If you ever find that you have lost your tunic, merely " +
      "<seek guidance> here. If the problem is larger than that, " +
      "contact the guildmaster.\n");
    AI(({"small banner","banner"}),"The banner is a green colour, " +
      "symbolizing that the guild is currently open to new members.\n");
    AI(({"den","small den"}),"It lies to the west.\n");
    AI(({"courtyard","inner courtyard"}),"It rests to the south, an open " +
      "and outside area.\n");
    AI(({"hall","great hall"}),"The gathering room of the Knights of " +
      "Solamnia is north.\n");
    AI("library","The famed library of Vingaard Keep is east of here.\n");

    AE(VROOM + "squire_board", "west", "@@check_good");
    AE(VROOM + "great_hall", "north", 0);
    AE(VLIB + "library", "east", "@@check_good");
    AE(VROOM + "inner_court", "south", 0);
    LIGHT;
    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
      "teleportation in this area... or is it something else?\n");

    reset_room();

    seteuid(getuid());
    restore_object(SAVE_FILE);
}

int
check_good()
{
    if (gOrdheus && E(gOrdheus) == TO && CAN_SEE(gOrdheus, TP))
    {
        if (TP->query_alignment() < 0)
        {
            gOrdheus->command("say Vingaard does not trust you, "+
                              TP->query_race_name()+ ", as such you are not " +
                              "welcome to pass in that direction.");
            return 1;
        }
    }
    return 0;
}

void
init()
{
    ADD("join","join!");
    ADA("sponsor");
    ADA("guidance");
    ADA("seek");
    ADA("read");
/*     ADD("grant_person", "grant"); Removed by Morrigan 02/2004 */
    ADD("leave", "leave!");
    ::init();
}

/* New function requiring the permission of the Conclave to Knight */
/* new members. In the future, will need to add the Grand Master   */
/* to those who my grant. (Maybe Council?)                         */
int
grant_person(string str)
{
    object target;

    NF("What ?\n");
    if (!(ADMIN)->is_conclave(TP->query_name()) &&
      (!(ADMIN)->is_grandmaster(TP->query_name())) &&
      (!(ADMIN)->is_assistant(TP->query_name())) &&
      (TP->has_position() != "General") &&
      (!TP->query_wiz_level()) )
    return 0;

    NF("Grant whom permission to join the Knighthood?\n");
    if (!str)
    return 0;

    if (!find_player(str) || !P(str, TO))
    return 0;

    target = P(str, TO);

    NF(target->query_name()+" is already a Knight!\n");
    if (MEMBER(target))
    return 0;

    NF("You have already granted "+target->query_name()+".\n");
    if (target->query_prop("_i_may_join") == TP->query_name())
    return 0;

    NF(C(target->query_name())+" has already been granted permiss"+
      "ssion to join by "+target->query_prop("_i_may_join")+".\n");
    if (target->query_prop("_i_may_join"))
    return 0;

    if (TP->query_prop("_i_granted") != target->query_name())
    {
    TP->add_prop("_i_granted", target->query_name());
    write("Are you sure you wish to grant "+target->query_the_name(TP)+"? Enter again to confirm...\n");
    return 1;
    }

    TP->remove_prop("_i_granted");
    target->add_prop("_i_may_join", TP->query_name());
    write("You grant "+target->query_the_name(TP)+" permission "+
      "to join the Knighthood.\n");
    say(QCTNAME(TP)+" grants "+QTNAME(target)+" permission to "+
      "join the Knighthood.\n", ({ target, TP }) );
    target->catch_message(TP->query_The_name(target)+" grants you permission to join the Knighthood.\n");
    return 1;
}

/********************* leave ************************************************/
int
leave(string str)
{
    int i, num;
    string squire, knight;

    NF("Leave what? The Solamnian Knights?\n");
    if (str != "The Solamnian Knights")
    return 0;

    if (!TP->query_prop("_i_typed_leave"))
    {
        gOrdheus->command("say If you truly wish to betray the Knights of "+
          "Solamnia, the ceremony is brief. You will take my sword, "+
          "end your life, and die with honour - that is the way of the "+
          "Knight.");
        gOrdheus->command("emote offers you his ceremonial sword, his face "+
          "showing no emotion.\n");

    TP->add_prop("_i_typed_leave", 1);
    return 1;
    }

    write("Performing the traditional ceremony, you begin the Solamnian "+
      "Death Chant...\n");
    TP->command("kchant");
    write("Having completed the song, you solemnly take the ceremonial "+
      "sword from Ordheus, and run it across your exposed throat...\n\n"+
      "Your world fades to black.\n");
    say(QCTNAME(TP)+" solemnly takes the ceremonial sword from Ordheus, "+
       "and runs it across "+POSSESSIVE(TP)+" throat...\n");
    TP->heal_hp(-TP->query_max_hp());

    /* added to remove special positions if the Knight quits... */
    restore_map(APPOINT_FILE);
    if (TP->has_position())
    {
    positions[TP->has_position()] = 0;
    TP->remove_position();
    save_map(positions, APPOINT_FILE);
    }

    if (TP->query_knight_level() > 2)
    {
    knight = TP->query_name();
    (ADMIN)->remove_knight_sponsorlist(knight);
    }

    if (TP->query_knight_level() < 3)
    {
    squire = TP->query_name();
    (ADMIN)->remove_squire_sponsorlist(squire);
    }

    TP->remove_cmdsoul(KNIGHT_SOUL);
    if (P("pal_med", TP))
    P("pal_med", TP)->remove_object();
    TP->update_hooks();

    LEAVE(TP);
    if (TP->query_knight_level() != 2)
    {
    TP->add_prop(LIVE_I_NO_CORPSE, 1);
    TP->do_die(TO);

    gOrdheus->command("emote kneels beside the fallen knight briefly, " +
      "and retrieves his "+
      "sword. Wiping the blade clean, he sheathes it, an expression of sadness "+
      "flashing on his face briefly. He motions at a nearby guard, who nods and "+
      "removes the corpse from the halls of the Keep.\n");
    }

    return 1;
}

/* The function to check to see if the player can join the guild
    * The reason we return 1 all the time here is that there is a 'join' command
* in the soul and thus our error messages would dissapear for the player.
*/
int
join(string str)
{
    object *ob, knight;
    int i;

    if (!str)
    {
    write("Join! Knights with whom?\n");
    return 1;
    }

    if (sscanf(str, "%s %s %s", str1, str2, whom ) != 3)
    {
    write("The syntax is: join! Knights with <name>.\n"
      + "Where <name> is the name of the player sponsoring you.\n");
    return 1;
    }

    if (str1 != "Knights" || str2 != "with")
    {
    write("You can't join anything but the Solamnian guild here.\n"
      + "Use 'join! Knights with <name>'.\n");
    return 1;
    }

    ob = FILTER_LIVE(all_inventory(this_object()));
    for (i = 0; i < sizeof(ob); i++)
    {
        write_debug("\nChecking: " + ob[i]->query_name() + "\n");
        write_debug("\nChecked against: " + whom + "\n");
        if (L(ob[i]->query_name()) == L(whom))
        {
            write_debug("\nVariable 'here' is equal to: " + here + "\n");
            if (here == 1)
            {
                write_debug("\n\twhom = " + whom +
                            "\n\tkname = " + kname +
                            "\n\tsname = " + sname +
                            "\n\tTP() = " + TP->query_name() + "\n");
                if (L(whom) == L(kname) && L(TP->query_name()) == L(sname))
                {
                    here = 2;
                    knight = ob[i];
                    break;
                }
            }
        }
    }

    if (here == 0)
    {
    write("There are no Solamnian Knights here of that name\n"
      + "who have sponsored you.\n");
    return 1;
    }
    if (here == 1)
    {
    write("You must be sponsored by that player first!\n");
    return 1;
    }

    if (!check_join(TP))
    return 1;

    /*  Removed by Morrigan 2/2004
     *    NF("You have not been granted permission to join by a Conclave member.\n");
     *    if (!TP->query_prop("_i_may_join"))
     *    return 0;
     */

    (ADMIN)->add_relation(C(kname),TP->query_name());
    here = 0;

    add_member(TP, "occupational",kname);
    write("Ok.\n");
    say(QCTNAME(TP) + " declares " + POSSESSIVE(TP) + " intent to join the " +
      "knighthood.\n");
    return 1;
}

/* Function name: sponsor()
* Purpose: To allow a member of a knight order to sponsor a player
*/
sponsor(string str)
{
    object *ob;
    int i, limit, tid;

    write_debug("\n" + C(TP->query_name()) + " just used 'sponsor'.\n");

    NF("Sponsor who?\n");
    if (!str)
        return 0;

    // Wizards are allowed to sponsor
    if (!TP->query_wiz_level())
    {
        if (!(MEMBER(TP)) )
        {
        write("You are not a Solamnian knight!\n");
        return 1;
        }
        if (TP->query_knight_level() < 3)
        {
        write("You are not a member of any of the knight orders.\n");
        return 1;
        }

        if (TP->query_knight_level() == 3 && TP->query_knight_sublevel() < 7)
        {
        write("You must have reached at least " + CROWN_TITLES[7] + " before " +
          "you can sponsor someone.\n");
        return 1;
        }
    }
    else
    {
        tid = extract(ctime(time()), 4, 15);
        write_file(JOINPATH, TP->query_real_name() + " sponsored " + str +
                             " " + tid + "\n");
        write("As a wizard you are allowed to sponsor, your actions" +
        " have been logged though, so make sure you have good reasson.\n");

    }

    if (TP->query_knight_sublevel() == 11)
        limit = 2;
    else if ((ADMIN)->is_assistant(TP->query_name()))
        limit = 1;
    /* maybe assistants to the conclave will have 2 squires in the future, too?
    */
    else
        limit = 1;

    if (TP->query_wiz_level())
    {
        limit = 0;
        if (member_array(TP->query_name(),GUILDMASTERS) >= 0)
            limit = 99999;
    }
    if (SPONSOR(TP->query_name()) >= limit && member_array(TP->query_name(),GUILDMASTERS) < 0)
    {
        write("You have already sponsored as many squires as you can " +
            "have.\n");
        return 1;
    }

    here = 0;
    ob = FILTER_LIVE(all_inventory(this_object()));
    for (i = 0; i < sizeof(ob); i++)
    {
        if (L(ob[i]->query_real_name()) == L(str))
        {
            if ( (!(MEMBER(ob[i]))) )
            {
                if (ob[i]->query_guild_member_occ())
                {
                    write("You cannot sponsor someone who is " +
                        "still in an occupational guild.\n");
                    return 1;
                }

                if (SPONSORED(ob[i]->query_name()))
                {
                    write("That player has already been sponsored.\n");
                    return 1;
                }
                write("You put your name forward to sponsor " + C(str) +
                  ".\n");
                write("If "+C(str)+" joins as your squire, "+
		  "you may then use the commands 'squirepromote' and "+
		  "'squiredemote' to reward or penalize your squire, "+
		  "respectively. Be forewarned that use of this command "+
		  "is logged and reviewable by the Conclave.\n");

                kname = TP->query_real_name();
                sname = str;
                say(C(kname) + " has put " + TP->query_possessive() +
                  " name forward to sponsor " + C(sname) + ".\n");
                here = 1;

                return 1;
            }
            if (MEMBER(ob[i]))
            {
                if (SPONSORED(ob[i]->query_name()))
                {
                    write("That player has already been sponsored.\n");
                    return 1;
                }

                (ADMIN)->add_relation(TP->query_name(),
                  ob[i]->query_name());
                write("You are now sponsoring " + ob[i]->query_name() +
                  ". As such, you may use the commands 'squirepromote' and "+
		  "'squiredemote' to reward or penalize your squire, "+
		  "respectively. Be forewarned that use of this command "+
		  "is logged and reviewable by the Conclave.\n");
                ob[i]->catch_msg("You are now being sponsored by " +
                  TP->query_name() + ".\n");
                return 1;
            }

        }
    }
    if (here == 0)
        return 0;
    return 1;
}



/* Function name: wiz_sponsor(str)
* Purpose: To allow a member of a knight order to sponsor a player
*/
wiz_sponsor(string str)
{
    object *ob;
    int i, limit, tid;

    write_debug("\n" + C(TP->query_name()) + " just used 'sponsor'.\n");

    NF("Sponsor who?\n");
    if (!str)
    return 0;
    here = 0;
    ob = FILTER_LIVE(all_inventory(this_object()));
    for (i = 0; i < sizeof(ob); i++)
    {
        if (L(ob[i]->query_real_name()) == L(str))
        {
            if ( (!(MEMBER(ob[i]))) )
            {
                if (SPONSORED(ob[i]->query_name()))
                {
                    write("That player has already been sponsored.\n");
                    return 1;
                }
                write("You put your name forward to sponsor " + C(str) +
                  ".\n");
                write("If "+C(str)+" joins as your squire, "+
		  "you may then use the commands 'squirepromote' and "+
		  "'squiredemote' to reward or penalize your squire, "+
		  "respectively. Be forewarned that use of this command "+
		  "is logged and reviewable by the Conclave.\n");

                kname = TP->query_real_name();
                sname = str;
                say(C(kname) + " has put " + TP->query_possessive() +
                  " name forward to sponsor " + C(sname) + ".\n");
                here = 1;

                return 1;
            }
            if (MEMBER(ob[i]))
            {
                if (SPONSORED(ob[i]->query_name()))
                {
                    write("That player has already been sponsored.\n");
                    return 1;
                }

                (ADMIN)->add_relation(TP->query_name(),
                  ob[i]->query_name());
                write("You are now sponsoring " + ob[i]->query_name() +
                  ". As such, you may use the commands 'squirepromote' and "+
		  "'squiredemote' to reward or penalize your squire, "+
		  "respectively. Be forewarned that use of this command "+
		  "is logged and reviewable by the Conclave.\n");
                ob[i]->catch_msg("You are now being sponsored by " +
                  TP->query_name() + ".\n");
                return 1;
            }

        }
    }
    if (here == 0)
        return 0;
    return 1;
}



/*
* This should check so that the player isn't
* a member in another major guild.
*/
int
check_join(object player)
{
    string lay_name;

    if (MEMBER(player))
    {
    write("You already a member of this guild, you can't join again.\n");
    return 0;
    }
    if (QRACE(player) != "human" && QRACE(player) != "dwarf" &&
#if 0
      /* won't work since QRACE doesn't return 'half-elf' anymore */
      QRACE(player) != "half-elf"
#else
      /* this check should still work. */
      !player->id("half-elf")
#endif
    )
    {
    write("The Knighthood does not allow members of your race "+
      "to join.\n");
    return 0;
    }

    if (BANISHED(player))
    {
    write("You are banished from this guild, no longer welcome.\n");
    return 0;
    }

    lay_name = player->query_guild_name_lay();

    setuid();
    seteuid(getuid());
    
    if (lay_name
        && !IN_ARRAY(lay_name, m_values(LAYMAN_MANAGER->query_allowed_laymans())))
    {
        write("You are presently allied to an organization that is not "
          + "allowed by the Conclave of the Knighthood. The "
          + "Knighthood demands the utmost commitment and dedication, "
          + "non-approved loyalties must be broken to join them.\n");
        return 0;
    }

    return 1;
}

int
join_us(object player, string type)
{
    if (player->query_alignment() < ALIGN_WARNING)
    {
    write("You are not good enough to be welcome in the Solamnian Guild\n");
    return 0;
    }

    if (player->query_guild_style("magic"))
    {
    write("You are already a member of a mage guild, you cannot join " +
      "us.\n");
    return 0;
    }

    if (player->query_guild_style("thief"))
    {
    write("You are already a member of a thief guild, you cannot join " +
      "us.\n");
    return 0;
    }

    if (this_player()->query_guild_member(type))
    {
    write("You are already a member of another " + type + " guild.\n");
    return 0;
    }

    return 1;
}

void
add_member(object player, string type, string sponsor)
{
    object shadow, medal;
    string name, tid, how, *soul_arr, gname;
    int result, i;

    if (!P("gOrdheus", TO))
    {
    write("The Knight who should have performed the ceremony is not " +
      "here. You will have to wait until he returns.\n");
    return;
    }

    if (ceremony_id > 0)
    {
    write("There is already an ongoing ceremony. Please wait!\n");
    return;
    }

    seteuid("Krynn");

    shadow = clone_object(O_SHADOW);
    gname = GUILD_NAME;

    result = shadow->shadow_me(player, type, "fighter", gname);
    if (result != 1)
    {
    write("The guilds you already have joined prevent you from " +
      "joining us.\n");
    return;
    }

    name = capitalize(player->query_real_name());
    tid = extract(ctime(time()), 4, 15);
    how = "joined the ";
    how = how + " guild.";

    write_file(JOINPATH, name + " " + how + " " + tid + "\n");
    write_file(KNIGHT_ALL_LOG, tid + " " + name + " " + how + "\n");

/*    write_file(KNIGHT_ALL_LOG, tid + " " + capitalize(kname)+
 *          " sponsored " +capitalize(name) + " with " +
 *          player->query_prop("_i_may_join")+"'s permission\n");
 * 
 * removed by Morrigan 2/2004, no grant necessary now
 */

    write_file(KNIGHT_ALL_LOG, tid + " " +capitalize(kname)+" sponsored "+
	capitalize(name)+"\n");

    seteuid("Krynn");
    if (type == "occupational")
    player->set_bit(GUILD_GROUP, MEMBER_BIT);

    if (!present("pal_med", player))
    {
    (medal = clone_object(MEDALPATH))->move(player, 1);
    medal->set_knight_level(L_SQUIRE);
    }

    soul_arr = player->query_cmdsoul_list();
    for (i = 0; i < sizeof(soul_arr); i++)
    player->remove_cmdsoul(soul_arr[i]);
    player->add_cmdsoul(KNIGHT_SOUL);
    for (i = 0; i < sizeof(soul_arr); i++)
    player->add_cmdsoul(soul_arr[i]);
    player->add_subloc("solamnian_subloc", this_object());
    player->update_hooks();

    player->set_skill(SS_PRESTIGE_ACC, 18100);
    player->set_skill(SS_PRESTIGE_ST, 26);
    player->set_skill(SS_CHARITY, 200);
    ceremony_id = set_alarm(1.0,3.0,"do_ceremony", player);

    /*player->setup_skill_decay();*/
    /* Remove pending skill decays immediately */
}

// * This is the new joining ceremony *
void
do_ceremony(object player)
{
    object  room = environment(player);

    switch(step)
    {
    case 0:
    player->catch_msg(QCTNAME(gOrdheus)+" steps forward and studies you and " +
      "your sponsor solemnly.\n");
    say(QCTNAME(gOrdheus)+" steps forward and studies "+ QTNAME(player) +
      " solemnly.\n");
    break;
    case 1:
    tell_room(room,"\n");
    break;
    case 2:
    tell_room(room, gOrdheus->query_The_name(TP)+" says: So you would be "+
      "a Knight of Solamnia?\n\n");
    break;
    case 3:
    tell_room(room, gOrdheus->query_The_name(TP)+" says: Know that " +
      "from this day forward, all that you do will be a " +
      "reflection upon the Knighthood.\n");
    break;
    case 4:
    break;
    case 5:
    tell_room(room,"\n");
    break;
    case 6:
    break;
    case 7:
    tell_room(room, gOrdheus->query_The_name(TP)+" says: Your sponsor will be "+
      "held accountable for your actions until such a day as you are deemed "+
      "ready to be Knighted yourself.\n");
    break;
    case 8:
    break;
    case 9:
    tell_room(room,"\n");
    break;
    case 10:
    tell_room(room, gOrdheus->query_The_name(TP)+" says: As a Knight you must "+
      "swear to uphold the ideals of the Knighthood, and dedicate yourself "+
      "fully to the Oath and to the Measure.\n");
    break;
    case 11:
    tell_room(room,"\n");
    break;
    case 12:
    tell_room(room, gOrdheus->query_The_name(TP)+" says: Without " +
      "honour, life is forfeit. You must strive to uphold your " +
      "honour above all else - even your life. Do you swear " +
      "by the Oath?\n");
    break;
    case 13:
    tell_room(room,"\n");
    break;
    case 14:
    player->command("kdeclare");
    break;
    case 15:
    tell_room(room, gOrdheus->query_The_name(TP) +" asks: Do you " +
      "swear to uphold the ideals of the Knighthood, to live by " +
      "the Measure, and to bring honour to your Sponsor?\n");
    break;
    case 16:
    tell_room(room,"\n");
    break;
    case 17:
    player->command("kswear");
    break;
    case 18:
    tell_room(room,"\n");
    break;
    case 19:
    write("Ordheus motions for you to kneel, and as you kneel before him he "+
      "performs the ceremonial Knighting, touching both of " +
      "your shoulders with his sword.\nOrdheus says: Arise, "+
      player->query_name()+", a Squire of Solamnia!\n");
    say(QCTNAME(gOrdheus)+" motions for " + QTNAME(player) + " to kneel, and "+
      "performs the ceremonial Knighting, touching both of "+QTNAME(player)+"'s "+
      "shoulders with his sword.\n"+
      QCTNAME(gOrdheus)+" says: Arise, "+player->query_name()+", a Squire "+
      "of Solamnia!\n");
    break;
    case 20:
    break;
    default:
    remove_alarm(ceremony_id);
    ceremony_id = 0;
    step = -1;
    }
    step++;
}

/*
* Function name: guidance
* Description:   Give the player back his medal
* Returns:       True if ok.
    */
int
guidance()
{
    string name;

    NF("You are not a member of this guild.\n");
    if (!MEMBER(TP))
    return 0;

    seteuid(getuid(TO));

    if (!TP->query_guild_member(GUILD_NAME))
    {
    write_file(GUIDANCEPATH, extract(ctime(time()), 4, 15) + " " +
      capitalize(TP->query_real_name()) +
      " lost the auto shadow :(\n");
    TP->clear_bit(GUILD_GROUP, MEMBER_BIT);
    NF("A strange error, I'm sorry but you have to join us again.\n");
    return 0;
    }

    NF("You already have your tunic.\n");
    if (present("pal_med",TP))
    return 0;

    write("The knight gives you a new tunic.\n");
    say(QCTNAME(TP) + " gets a new tunic.\n");

    clone_object(MEDALPATH)->move(TP);
    write_file(GUIDANCEPATH, extract(ctime(time()), 4, 15) + " " +
      capitalize(TP->query_real_name()) +
      " lost the tunic but got a new one.\n");

    return 1;
}

/*
* Function name: seek (guidance)
* Description:   Give the player back his tunic
* Arguments:     None
* Returns:       True if ok.
    */
int
seek(string str)
{
    NF("Seek what?\n");
    if (str != "guidance")
    return 0;
    return guidance();
}

/* Block out none members */
int
members()
{
    seteuid(getuid(TO));

    if (MEMBER(TP))
    {
    if (!present("pal_med", TP))
    {
        write("You haven't got the tunic, seek guidance first.\n");
        return 2;
    }
    return 0;
    }

    if (P("gOrdheus", TO))
    {
    if (BANISHED(TP))
    {
        NF("The Knight recognizes you as banished from the guild, " +
          "'Stay out!', he says, 'We don't want you here!'\n\n");
        return 2;
    }
    else
    if (TP->query_alignment() < -200)
    {
        NF("Your evilness shines through, and the Knight " +
          "stops you.\n");
        return 2;
    }
    else
        write("The Knight lets you pass and welcomes you as a Guest.\n");
    }

    return 0;
}

int
read(string str)
{
    NF("Read what page? Use 'read <page number>'.\n");
    if (!str)
    return 0;

    switch(str)
    {
    case "book":
    case "index":
    str = "1";
    case "1":
    case "2":
    case "3":
    case "4":
    case "5":
    case "6":
    case "7":
    case "8":
    case "9":
    case "10":
    case "11":
    case "12":
    case "13":
    case "14":
    case "15":
    case "16":
    case "17":
    case "18":
    case "19":
    case "20":
    case "21":
    case "22":
    case "23":
    case "24":
    case "25":
    case "26":
    case "27":
    case "28":
    case "29":
    case "30":
    write("You turn in the book to page "+str+" and begin to read...\n");
    say(QCTNAME(TP)+" turns to a page in the book and begins to read.\n");
    TP->more(read_file(VTEXT + str), 0);
    break;
    default:
    NF("There is no page numbered "+str+" to read in the book.\n");
    return 0;
    }

    return 1;
}

void
write_debug(string str)
{
   object wizard = find_player("boron");

   if (!objectp(wizard))
     return;

   if ( (environment(wizard) == environment(TP) ) )
      wizard->catch_tell(str);

}
