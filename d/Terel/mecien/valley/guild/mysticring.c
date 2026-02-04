/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* This comment tells emacs to use c++-mode -*- C++ -*- */
/* The mystic silver ring */

inherit "/std/spells";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <options.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP              this_player()
#define TO              this_object()
#define ETO             environment(TO)
#define ETP             environment(TP)
#define ALCHECK(xx)     ((xx)->query_alignment() >= JOIN_LIM)
#define TRUE_MEMBER(xx) (MEMBER(xx) && ALCHECK(xx) && QM_RANK(xx) >= 0)
#define MORE_OBJ        "/std/board/board_more"
#define MYSTIC_S_OWNER  "_mystic_s_owner"

/*
 * Global variables
 */

static object cast_place;
static string spell_verb;
static int    id_destroy = 0;
mapping office_map;

/*
 * Prototypes
 */
public varargs void soul(object ob, int silent);
public void delay_msg(object new);
public int  allowed(object ob);
public void update_spells(object ob);
public void destroy_ring();
private string pad(string str, int z_length);

/*
 * Function name: query_auto_load
 * Description:   Make this object autoloading
 * Returns:       The filename of this object
 */
public string
query_auto_load()
{
   if (query_prop(MYSTIC_S_OWNER) != ETO->query_real_name())
       return "";

   add_prop(OBJ_M_NO_DROP, 1);

   return MASTER + ":" + 2;
}

public void
reset_object()
{
    if (!ETO || !living(ETO)) return;
    
    if (allowed(ETO))
        soul(ETO, 1);
    else
        delay_msg(ETO);
}

/*
 * Function name: init
 */
public void
init()
{
    ::init();
    if (ETO == TP && T_WIZ(TP)) {
        add_action("mystic", "mystic", 1);
    }
    add_action("touch_ring", "touch", 1);
/*
 * Why on earth does this code exist?!? It blatantly removes the occupational
 * guild shadow of every person that even walks in the room with the ring
 * laying on the floor! /Mercade
 *
        if (TP->remove_guild_occ()) {
            write("You do not belong to the Order any longer.\n");
            TP->remove_cmdsoul(MYSTIC_SOUL);
            TP->update_hooks();
            return;
	}
 */
}

/*
 * Function name: update_spells
 * Description:   update the list of spells available to the player
 *                add spells via add_spell
 * Arguments:     ob - the player
 */
public void
update_spells(object ob)
{
   /* First we remove all mystic spells so that a mystic who has
    * lost a rank, for some reason, doesn't keep the old spells
    * when update_spells() is called.
    */
   if (sizeof(query_verbs()))
       map(query_verbs(), remove_spell);
   
   /* Add spells that are in the testing phase */
   if (T_WIZ(ob)) {
      add_spell("mortus",     "cast_spell", "ancient death");
      add_spell("umbra",      "cast_spell", "nether form");
      add_spell("somnus",     "cast_spell", "mystic slumber");
      add_spell("magus",      "cast_spell", "ancient magic");
      add_spell("agmen",      "cast_spell", "ancient army");
      add_spell("canis",      "cast_spell", "mystic hound");
      add_spell("colo",       "cast_spell", "mystic cultivation");
      add_spell("pestis",     "cast_spell", "ancient plague");
      add_spell("tegere",     "cast_spell", "mystic mask");
      add_spell("carcarem",   "cast_spell", "ancient prison");
      add_spell("amicus",     "cast_spell", "mystic friend");
      add_spell("baculum",    "cast_spell", "mystic staff");
      add_spell("sanguis",    "cast_spell", "mystic blood");
      add_spell("caelum",     "cast_spell", "holy land");
      add_spell("animus",     "cast_spell", "mystic spirit");
      add_spell("saxum",      "cast_spell", "ancient stone");
      add_spell("venator",    "cast_spell", "nether stalker");
      add_spell("requiem",    "cast_spell", "ancient buriel");
      add_spell("venustas",   "cast_spell", "mystic charm");
   }

/* These spells have been disabled by the AoB, please refer
 to the mail. Do not implement these spells until they have been
reapproved and proper documentation is in place. */

   switch (ob->query_spell_level())
   {
/*
      case 120..1000:
      if (ob->query_mystic_rank() > 5){
         add_spell("mirabilis", "cast_spell", "holy mystery");
      }
      case 110..119:
      if (ob->query_piety() > 700) {
          add_spell("carrus",   "cast_spell", "ancient chariot");
      }
      add_spell("perditus",     "cast_spell", "divine wrath");
      case 100..109:
      if (ob->query_piety() > 400) {
         add_spell("epulum",    "cast_spell", "ancient feast");
         add_spell("vita",      "cast_spell", "holy life");
      }
      add_spell("caligo",       "cast_spell", "ancient curse");
      add_spell("paupertas",    "cast_spell", "ancient poverty");
      add_spell("ignis",        "cast_spell", "sacred fire");
      case 95..99:
      if (ob->query_piety() > 300) {
         add_spell("donum",     "cast_spell", "sacred gift");
         add_spell("caecus",    "cast_spell", "nether mantle");
         add_spell("sanctus",   "cast_spell", "holy word");
         add_spell("arbor",     "cast_spell", "sacred tree");
         add_spell("tutela",    "cast_spell", "divine protection");
      }
      add_spell("simulacrum",   "cast_spell", "mystic creation");
      add_spell("angelicus",    "cast_spell", "angelic summons");
      add_spell("immuto",       "cast_spell", "mystic change");
      case 90..94:
      if (ob->query_piety() > 200) {
         add_spell("hasta",     "cast_spell", "heavenly strike");
         add_spell("sentire",   "cast_spell", "mystic sense");
         add_spell("locusta",   "cast_spell", "locust plague");
         add_spell("vepres",    "cast_spell", "nether thorns");
         add_spell("oblivisci", "cast_spell", "dark unknowing");
         add_spell("purus",     "cast_spell", "holy purify");
      }
      add_spell("cantus",       "cast_spell", "holy song");
      add_spell("anguis",       "cast_spell", "arcane warden");
      add_spell("lacerna",      "cast_spell", "mystic mantle");
      add_spell("manes",        "cast_spell", "mystic death");
      add_spell("magnus",       "cast_spell", "divine heroism");
      case 80.. 89:
      if (ob->query_piety() > 200) {
         add_spell("verbum",    "cast_spell", "mystic word");
         add_spell("torris",    "cast_spell", "mystic fire-brand");
         add_spell("salus",     "cast_spell", "heavenly visitation");
         add_spell("dictum",    "cast_spell", "ancient voice");
      }
      add_spell("astrum",       "cast_spell", "summon star");
      add_spell("arcere",       "cast_spell", "mystic hindrance");
      add_spell("sigilla",      "cast_spell", "ancient runes");
      add_spell("audire",       "cast_spell", "mystic ear");
      case 70..79:
      add_spell("tonitrus",     "cast_spell", "ancient thunder");
      add_spell("portus",       "cast_spell", "mystic recall");
      add_spell("fulmen",       "cast_spell", "divine lightning");
      add_spell("mittere",      "cast_spell", "mystic sending");
      add_spell("venenare",     "cast_spell", "mystic poison");
      case 60..69:
      add_spell("inimicus",     "cast_spell", "mystic enemies");
      add_spell("ardere",       "cast_spell", "mystic aura");
      add_spell("sanare",       "cast_spell", "divine heal");
      add_spell("tempestus",    "cast_spell", "summon storm");
      add_spell("fortudo",      "cast_spell", "divine courage");
      case 50..59:
      add_spell("mutus",        "cast_spell", "mystic silence");
      add_spell("tueri",        "cast_spell", "summon guardians");
      add_spell("pacis",        "cast_spell", "summon peace");
      add_spell("obtutus",      "cast_spell", "mystic sight");
      add_spell("vires",        "cast_spell", "ancient energy");
      case 40..49:
      add_spell("flammis",      "cast_spell", "mystic fire");
      add_spell("fervere",      "cast_spell", "spiritual ferment");
      add_spell("nomen",        "cast_spell", "mystic naming");
      add_spell("vocare",       "cast_spell", "mystic summoning");
      case 30..39:
      if (ob->query_piety() > 100) {
          add_spell("avis",     "cast_spell", "dark omen");
          add_spell("malo",     "cast_spell", "sense evil");
      }
      add_spell("imago",        "cast_spell", "soul sight");
      add_spell("visus",        "cast_spell", "mystic eye");
      add_spell("panis",        "cast_spell", "mystic bread");
      add_spell("validus",      "cast_spell", "mystic strength");
      add_spell("venenare",     "cast_spell", "mystic poison");
      add_spell("circa",        "cast_spell", "mystic circle");
      case 20..29:
      add_spell("nubes",        "cast_spell", "mystic cloud");
      add_spell("lumen",        "cast_spell", "sacred light");
      add_spell("lenire",       "cast_spell", "mystic calm");
      add_spell("tenebrae",     "cast_spell", "ancient darkness");
      add_spell("mederi",       "cast_spell", "mystic heal");
      add_spell("stella",       "cast_spell", "mystic starbolt");
      case 1..19:
      add_spell("voce",         "cast_spell", "mystic voice");
      add_spell("beatus",       "cast_spell", "mystic blessing");
      break;

      default:
      break;
*/
   }
}

/*
 * Function name: create_spells
 * Description:   Initialization function
 */
void
create_spells()
{
   set_name("ring");
   add_name(MYSTIC_RING);
   set_adj(({"silver","mystic"}));
   set_short("silver ring");
   set_pshort("silver rings");

   set_long("A simple silver ring inscribed with an intricate star.\n");

   add_prop("no_sacrifice", 1);

   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);
}

public mixed
cast_spell(string str)
{
   string spell_file;

   /*
    * The spells have been disabled by Rohim.
    * They are not to be set back until the AoB have approved this.
    */

   /*
   return "You concentrate hard, but can't feel anything but a strange " +
       "emptiness.\n";
   */

   if (allowed(TP)) {
      if (TP->query_piety() < PIETY_SPELL_LIM) return "You feel empty.\n";
      TP->set_piety(TP->query_piety() - 1);
      if (cast_place != ETP)
        return "You lose your concentration on the spell due to " +
               "your rapid movement.\n";
      seteuid(getuid());
      spell_file = SPELL_DIR + spell_verb;
      return call_other(spell_file, spell_verb, str);
   } else {
      set_alarm(4.0, -1.0, &delay_msg(TP));
      return 0;
   }
}

/*
* Function name: query_spell_time
* Description:   How long time will it take to cast a spell?
* Arguments:     verb - The spell verb
* Returns:       The time it will take. Real casting time will be time + 2
*/
int
query_spell_time(string verb)
{
   spell_verb = verb;
   cast_place = ETP;
   if (verb == "perditus") return 4;
   if (verb == "portus") return 10;
   if (verb == "immuto") return 10;
   if (verb == "carrus") return 10;
   if (verb == "vita") return 5;
   return 0;
}

public void
enter_env(object new, object old)
{
   ::enter_env(new, old);
   
   if (!living(new)) return;
   if (allowed(new))
      set_alarm(2.0, -1.0, &soul(new));
   else
      set_alarm(2.0, -1.0, &delay_msg(new));

   return;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    
    if (!from || !living(from)) return;
    
    if (query_prop(MYSTIC_S_OWNER) == from->query_real_name()) {
        from->remove_cmdsoul(MYSTIC_SOUL);
        from->update_hooks();
    }
}

public void
delay_msg(object new)
{
   TO->move(environment(new));
   if (MEMBER(new)) {
      tell_object(new, "Because of your evil actions the " +
                  short() + " slips away from you.\n");
   } else {
      tell_object(new, "You are not entitled to have the " +
                  short() + "!\n");
      tell_object(new, "You feel forced to drop it.\n");
   }
   tell_room(environment(new), QCTNAME(new) + " drops a " +
             short() + ".\n", new);
   if (!id_destroy) id_destroy = set_alarm(10.0, -1.0, "destroy_ring");
}

public varargs void
soul(object ob, int silent = 0)
{
   int rank, i;
   string *soul_list;
   object shadow;

   if (!ob || !living(ob)) return;

   if (query_prop(MYSTIC_S_OWNER) != ob->query_real_name()) return;
   
   seteuid(getuid());
   
   office_map = ([ ]);
   restore_object(OFFICE_DATA);
   
   if (environment(TO) == ob) {
      if (ob->query_present_rank() || T_WIZ(ob)) {
         if (silent == 0) {
             ob->catch_msg("You are a dedicated disciple " +
                   "of the Ancient Ones.\n");
             for (i=0; i<sizeof(OFFICES); i++) {
                 if (office_map[OFFICES[i]] == ob->query_real_name()) {
                     ob->catch_msg("You are appointed by the Patriarch as " +
                                   "holder of the Office of " +
                                   capitalize(OFFICES[i]) + ".\n");
                     break;
                 }
            }
         }
      } else {
         rank = ob->query_mystic_rank();
         ob->catch_msg("You do not fulfill the requirements of a " +
               ob->query_guild_title_occ() + ".\n");
         ob->catch_msg("You lose some of your spells.\n");
      }
      if (ob->query_alignment() < JOIN_LIM + 30) {
         ob->catch_msg("Thou art close to losing the powers of " +
            "the Ancient Ones because of your evil actions.\n");
      }
   }
   update_spells(ob);


  /*
   * We need to have the mystic soul as the first soul in the list
   * of command souls.  I wish there was a better way to do this.
   */

   soul_list = ob->query_cmdsoul_list();
   
   if (member_array(MYSTIC_SOUL, soul_list) == -1) {
      if (ob->query_wiz_level() == 0) {
         for (i = 0; i < sizeof(soul_list); i++)
            ob->remove_cmdsoul(soul_list[i]);
         ob->add_cmdsoul(MYSTIC_SOUL);
         for (i = 0; i < sizeof(soul_list); i++)
            ob->add_cmdsoul(soul_list[i]);
      } else {
         ob->add_cmdsoul(MYSTIC_SOUL);
      }
      ob->update_hooks();
   }
}

public int
allowed(object ob)
{
   if (T_WIZ(ob)) return 1;
   if (TRUE_MEMBER(ob)) return 1;
   return 0;
}

public void
destroy_ring()
{
   if (ETO->query_prop(ROOM_I_IS))
      tell_room(ETO, "The "+short()+" vanishes.\n");
   remove_object();
}

/*
* Function name: list_spells
* Description:   This function is called to list the spells from
*                the player soul when the command "spells" is typed.
*/
public void
list_spells()
{
   int i, i1, vsize, vlim, fold;
   string s1, s2;
   string text;

   vsize = sizeof(verb_list);
   vlim = vsize;
   fold = vsize/2;
   if (vlim > fold) vlim = fold;
   if (vlim + fold == vsize - 1) {
      vlim++;
      fold++;
   }
   text = "------------------------*** The Ancient Mystic Order " +
      "***----------------------\n";

   for (i = 0; i < vlim; i++) {
      s1 = pad(verb_list[i], 15) + pad(name_list[i], 21);
      i1 = fold + i;
      if (vsize != vlim && i1 < vsize) {
         s2 = pad(verb_list[i1], 15) + name_list[i1];
         text += s1 + " | " + s2 + "\n";
      } else {
         text += s1 + " |\n";
      }
   }
   text += "-----------------------------------------------------" +
      "-------------------------\n";

   if (fold > TP->query_option(OPT_MORE_LEN)) {
     seteuid(getuid());
     clone_object(MORE_OBJ)->more(text);
   } else {
     write(text);
   }
}

private string
pad(string str, int z_length)
{
   string space;

   space = "                                                 ";
   return str + extract(space, 0, z_length - strlen(str));
}

int
query_spell_mess(string verb)
{
   write("You start to focus your attention on the powers of the " +
      "Ancient Ones.\n");
   say(QCTNAME(TP) + " focuses " + TP->query_possessive() +
      " attention on something mysterious.\n");
   return 1;
}


/*
* Function name: init_arg
* Description:   Called when autoloading
*/
void
init_arg(string str)
{
   add_prop(MYSTIC_S_OWNER, TP->query_real_name());
   set_alarm(3.0, -1.0, "notify_icon_holders");
}

/*
 * Function name: notify_icon_holders
 * Description:   send a message to all guildmembers logged in
 *                (only those who possess the icon)
 */
void
notify_icon_holders()
{
   object *ul;
   int i;

   ul = users();
   for (i = 0; i < sizeof(ul); i++)
     if (MEMBER(ul[i]) && present(MYSTIC_ICON, ul[i]) && ul[i] != ETO)
       ul[i]->catch_msg("You feel the holy icon grow warm.\n");
}

/*
 * Function name: mystic
 * Description:   Used only by wizards to do debugging of the guild.
 * Arguments:     "join" or "leave"
 */
public int
mystic(string str)
{
    object shadow;
    
    if (!T_WIZ(TP)) return 0;
    
    notify_fail("mystic join/leave?\n");
    if (str != "join" && str != "leave") return 0;
    
    if (str == "join" && !MEMBER(TP)) {
        seteuid(getuid());
        shadow = clone_object(MYSTIC_SHADOW);
        if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD) != 1) {
            notify_fail("For some unknown reason you cannot " +
                        "join this guild.\n");
            "/secure/master"->do_debug("destroy", shadow);
            return 0;
        }
        write("You belong to the Order.\n");
        soul(TP);
        return 1;
    } else if (str == "leave" && MEMBER(TP)) {
        if (TP->remove_guild_occ()) {
            write("You do not belong to the Order any longer.\n");
            TP->remove_cmdsoul(MYSTIC_SOUL);
            TP->update_hooks();
            return 1;
        }
        notify_fail("Couldn't remove you properly!\n");
    }
    return 0;
}

public int
touch_ring(string str)
{
    int rank;
    
    notify_fail("Touch what?\n");
    if (!str || !id(str)) return 0;
    
    write("You touch the " + short() + ".\n");
    
    rank = TP->query_mystic_rank();
    if (environment(TO) == TP && MEMBER(TP) && rank >= 0) {
       if (TP->query_present_rank() || T_WIZ(TP)) {
          TP->catch_msg("You are a dedicated disciple " +
                "of the Ancient Ones and you fulfill the " +
                "requirements of a " + TP->query_guild_title_occ() + ".\n");
       } else {
          TP->catch_msg("You do not fulfill the requirements of a " +
                TP->query_guild_title_occ() + ".\n");
       }
       if (TP->query_alignment() < JOIN_LIM + 30) {
          TP->catch_msg("Thou art close to losing the powers of " +
              "the Ancient Ones because of your evil actions.\n");
       }
       update_spells(TP);
    }
    return 1;
}
