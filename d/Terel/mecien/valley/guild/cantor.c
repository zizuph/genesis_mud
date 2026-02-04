/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/* Chatting monster */
inherit "/d/Terel/std/mystic";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO      this_object()
#define TP      this_player()
#define ETO     environment(TO)
#define ETP     environment(TP)
#define EN environment
#define co command
#define in clone_object("/d/Terel/mecien/valley/guild/obj/incense_cloud")

int going;
int process;
int time;
object ob;



burn(object who){
   if(who->query_prop("blessed") < 1){
   who->heal_hp(-300);
  who->catch_msg("You are burned badly!\n");
  return 1;
   }
if(who->query_prop("blessed") && who->query_alignment() > 300){
   who->catch_msg("The fire does not burn you but fills you with a mighty power!\n");
   who->add_mana(300);
   return 1;
   }
}

bells(object who){
   if(!MEMBER(who)) return 0;
   if(MEMBER(who)) who->catch_msg("You hear the bells of the shrine ringing out an ancient and familiar hymn!\n");
}

dbells(object who){
   if(!MEMBER(who)) return 0;
  if(MEMBER(who)) who->catch_msg("You hear the bells of the shrine ringing out an ancient and somber hymn.\n");
}
fbells(object who){
   if(!MEMBER(who)) return 0;
  if(MEMBER(who)) who->catch_msg("You hear the bells of the shrine ringing out a mysterious hymn, filling you with a fiery desire.\n");
}
public void
do_things()
{
   object robe, icon;
   
   seteuid(getuid());
   
   robe = clone_object(GUILD_DIR + "quest/hrobe");
   robe->move(TO);
   robe->add_prop(MYSTIC_ARMOUR, 1);
   
   icon = clone_object(GUILD_DIR + "obj/icon");
   icon->add_prop(OBJ_M_NO_STEAL, 1);
   icon->move(TO);
   
   command("wear robe");
}

public void
create_monster()
{
   ::create_monster();
   
   set_name("mieriys");
   add_name("cantor");
   set_living_name("mieriys");
   set_race_name("human");
   set_adj("old");
   add_adj("holy");
   set_title("the Holy Cantor");
   set_short("Mieriys the Holy Cantor");
   set_long("A man of great learning and wisdom, he is the master of "
      +"ceremonies here in the great shrine. In him abides the "
      +"ancient powers. He has deep blue eyes that sparkle like "
      +"starlight upon the seas, his hair is long and pale, almost "
      +"the color of flax. In him there is great age, but he looks "
      +"only mid-aged. He wear a white cowl, a pale blue mantle, "
      +"a silver scapular and a silver mitre.\n");
   set_stats(({ 35, 56, 112, 132, 124, 102}));
   set_alignment(845);
   set_appearance(96);
   set_hp(20000);
   set_mana(9000);
   
   set_rank(MYSTIC_ARCHON);
   set_skill(SS_DEFENCE, MYSTIC_MAX_DEFENCE);
   set_skill(SS_SPELLCRAFT, MYSTIC_MAX_SPELLCRAFT);
   set_skill(SS_LANGUAGE, MYSTIC_MAX_LANGUAGE);
   set_skill(SS_FORM_CONJURATION, MYSTIC_MAX_CONJURATION);
   set_skill(SS_ELEMENT_LIFE, MYSTIC_MAX_LIFE);
   set_piety(1000);
   set_blessed(1);
   enable_auto_hail();
   
   add_prop("no_show_title", 1);
   set_all_hitloc_unarmed(95);
   add_prop(LIVE_I_ALWAYSKNOWN, 1);
   
   add_ask(({"about mountain top", "about mountain of the sky"}),
      "In the icy mountains shall ye find it.\n");
   add_ask(({"about the sky", "the air", "about the winds",
            "about the air", "about air"}),
      "The Cantor sings: Upon the mountain top shall all be found.\n");
   add_ask(({"where is the chapel", "about chapel", "life chapel",
            "chapel", "entrance", "about holy chapel"}),
      "The Cantor sings: Place thy right hand upon the disk.\n");
   add_ask(({"door", "about door", "key", "about key"}),
      "The Cantor intones: When thou hast found the door, stand before it " +
      "and speak aloud, let Truth be known.\n");
   add_ask(({"about life", "life magic", "living powers"}),
      "The Cantor says:  Seek the Holy Chapel of Life.\n");
   
   set_act_time(5);
   add_act("emote intones a long canticle in honor of the stars.");
   add_act("emote kneels down and prays before the altar.");
   add_act("emote lights a bit of incense and burns it before the altar.");
   add_act("@@cant");
   add_act("hold icon");
   add_act("@@try_cer");
   
   set_cact_time(1);
   add_cact("@@summon");
   add_cact("@@heal");
   add_cact("@@word");
   set_chat_time(5);
   
   set_alarm(2.0, -1.0, do_things);
}


try_cer(){
   if(process) return 0;
   if(random(1000) > 970) set_alarm(1.0, -1.0, "do_cer");
    if(process > 0) return 0;
   if(random(10000) > 9900) set_alarm(2.0, -1.0, "do_dead");
  if(process > 0) return 0;
  if(random(10000 > 8000)) set_alarm(3.0, -1.0, "do_fire");
}

do_dead(){
  if(process) return 0;
   process = set_alarm(3.0, 12.0, "te_deum");
  map(users(), dbells);
}

do_cer(){
  if(process) return 0;
   process = set_alarm(3.0, 12.0, "vespers");
   map(users(), bells);
}

do_fire(){
  if(process) return 0;
   process = set_alarm(3.0, 12.0, "fire_prayer");
  map(users(), fbells);
}

fire_prayer(){
   object obp, dust, soot, silver, st;
  int i;
   switch(time){
   case 0:
  seteuid(getuid());
   ob = clone_object("/d/Terel/mecien/valley/guild/lewen");
   ob->move_living("arrives", EN(TP));
  co("say The hour has come...");
   co("emote kneels down.");
  break;
   case 2:
    co("say Let us proceed to the place where our purity is born");
  ob->co("mnod mieriys");
   break;
   case 3:
   ob->co("w");
   co("w");
   break;
   case 4:
   co("say Let Glory come to us who pray");
    co("emote holds aloft his censer, fanning out a cloud of incense.");
  in->move(EN(TO));
  break;
    case 5:
   co("n");
   ob->co("n");
   break;
   case 6:
   co("say Life burns with a Fire, for within us is the Fire of Sacred Mystery");
    co("pray");
    co("emote holds aloft his censer, fanning out a cloud of incense.");
  in->move(EN(TO));
   break;
   case 7:
   ob->co("n");
    co("n");
   break;
  case 8:
   co("say Let the Twelve be justified through our sacred ways...");
    co("emote holds aloft his censer, fanning out a cloud of incense.");
  in->move(EN(TO));
    co("pray");
   break;
   case 9:
   co("n");
    ob->co("n");
  break;
  case 10:
    co("emote holds aloft his censer, fanning out a cloud of incense.");
  in->move(EN(TO));
    break;
  case 11:
   ob->co("n");
    co("n");
  break;
   case 12:
   co("say Now I pray, that as we ascend, our hearts shall be filled with the spirit of the Stars, for we shall need them in the face of such Glory, for the Shining Truth above holds a blinding Wisdom");
    co("emote holds aloft his censer, fanning out a cloud of incense.");
  in->move(EN(TO));
   break;
   case 13:
   co("up");
    ob->co("up");
   co("s");
  ob->co("s");
  break;
  case 14:
   co("say Of all things, this place is Most True...");
   co("sign");
   ob->co("sign");
   ob->co("pray");
    break;
   case 15:
   co("emote whispers some unknown prayer, gazing up at the inscription.");
   ob->co("emote kneels down, praying silently.");
  break;
  case 16:
  co("point inscription");
   co("say BEHOLD! Here is written what is Truth, here is written what we must be!");
  co("pray");
   break;
   case 17:
    co("say Here shall I lay my mark, let these clouds of incense stand as my prayer, for I have nothing great to offer");
    co("emote holds aloft his censer, fanning out a cloud of incense.");
  in->move(EN(TO));
   break;
   case 18:
  co("sign");
  co("s");
   ob->co("sign");
   ob->co("s");
   break;
   case 19:
   co("shout BEHOLD THE FIRE! The Flame of Truth!");
  co("emote lays himself prostrate upon the ground.");
   ob->co("pray");
     break;
  case 20:
    co("emote stands up and approaches the flame.");
   co("say Within Thee do I see many things, but great enough I am not to see beyond, for I have not the Eyes of Prophecy, nor the Heart of Eternity");
   co("pray");
  break;
  case 21:
    co("say Sacred Fire, take this as a meek offering from the lowliness of this Order");
 co("pray");
  break;
   case 22:
    co("emote holds up his hands and casts something into the fire!");
  co("say Guard us well Sacred Fire, for we are empty without your strength");
   break;
  case 23:
  tell_room(EN(TO), "The fire begins to grow greater and greater, you fear it will soon consume everything in the chamber!\n");
   co("emote kneels down, trembling as the fire approaches.");
  break;
   case 24:
     co("pray");
    tell_room(EN(TO), "The fire roars throughout this place, covering you! Moving rapidly it enters your mouth and lungs as you breath!\n");
    map(all_inventory(EN(TO)), burn);
  break;
   case 25:
    co("emote stands tall, unburned and full of mysterious power!");
    co("say I thank Thee, Mighty Powers of Mystery, that you have chosen us, the Ancient Order worthy to behold your Glory, I pray it shall ever be so!");
   co("emote kisses the ground.");
   ob->co("mnod cantor");
   break;
   case 26:
   co("say All things are accomplished");
   co("pray");
    break;
   case 27:
   co("n");
   co("n");
   co("down");
   co("s");
    co("s");
   co("s");
   co("s");
  co("e");
  ob->co("n");
   ob->co("n");
   ob->co("down");
  ob->co("s");
  ob->co("s");
   ob->co("s");
   ob->co("s");
   ob->co("e");
  ob->co("n");
   ob->co("emote leaves.");
  ob->remove_object();
  break;
   default:
   process = 0;
   remove_alarm(process);
   }
  time++;

}


vespers(){
   switch(time){
      case 0:
      ob = clone_object("/d/Terel/mecien/valley/guild/lewen");
      ob->set_chat_time(0);

      TO->set_act_time(0);
  TO->clear_act();
      ob->add_prop(LIVE_I_ALWAYSKNOWN, 1);
      ob->set_skill(130008, 1);
   ob->move_living("arrives", EN(TO));
      command("emote looks upwards and nods solemnly.");
      command("ms It is time");
      break;
      case 1:
      TO->command("w");
      TO->command("w");
      if(ob) ob->command("w");
      ob->command("w");
      break;
      case 2:
      command("emote kneels down and prays silently.");
      command("kisses the floor.");
   break;
      case 3:
      command("emote prays aloud: Oh Ye Mighty Elders, bless these hallowed halls, for we who dwell herein do give Thee homage");
      command("emote lowers his head.");
      break;
      case 4:
      if(ob) ob->command("emote brings forth a censer and presents it reverently.");
      command("emote fills the censer with incense.");
      command("emote lights the incense.");
      command("pray");
      command("emote takes hold of the censer and blesses it with his hand.");
      break;
      case 5:
      command("emote waves his censer before the first statue.");
      command("emote prays aloud: Oh Bringer of the Sun, shine down upon us, that we may behold your Glory!");
      command("pray");
      break;
      case 6:
      command("emote waves his censer before the second statue.");
      command("emote prays aloud: O Great Lady, Beauty of the Sacred Moons, enchant us with Thy gaze");
      command("pray");
      break;
      case 7:
      command("emote traces his censer before the before the third statue.");
      command("emote prays aloud: O Keeper of the Celestial Ways, guide us through the world of dreams and bring us to a world of Truth");
      command("pray");
      break;
      case 8:
      command("emote waves his censer before the fourth statue.");
      command("emote prays aloud: Mistress, I have heard Thy cry upon the Wind, I do harken to Thy call, for you are my Song");
      command("pray");
      break;
      case 9:
      command("emote waves his censer before the fifth statue.");
      command("emote prays aloud: You are my Peace, standing before the tall oaks, Guardian of the arbors of Antiquity");
      command("pray");
      break;
      case 10:
      command("emote waves his censer before the sixth statue.");
      command("emote prays aloud: O how we are Plentiful with Thee to watch over us, for in the Clouds art thou, Lord, for Wind and Storm hear all you command");
      command("pray");
      break;
      case 11:
      command("emote waves his censer before the seventh statue.");
      command("emote prays aloud: I cry unto Thee, Mediator, for when I have no hope, I know that in Truth you will lift me up");
      command("pray");
      break;
      case 12:
      command("emote waves his censer before the eigth statue.");
      command("emote prays aloud: For in Thou shall I know all things, for Thy Lore is greatest");
      command("pray");
      break;
      case 13:
      command("emote waves his censer before the ninth statue.");
      command("emote prays aloud: Mighty are Thy Makings, we are humbled before the gifts that Thou hast bestowed upon us");
      command("pray");
      break;
      case 14:
      command("emote waves his censer before the tenth statue.");
      command("emote prays aloud: Of all things, Thy vision is greatest, for in the Dead is nothing hidden from Thy gaze");
      command("pray");
      break;
      case 15:
      command("emote waves his censer before the eleventh statue.");
      command("emote prays aloud: How Willing art Thou, My Heart, for Thou dost see all that is within us, my soul naked before Thee");
      command("pray");
      break;
      case 16:
      command("emote waves his censer before the twelfth statue.");
      command("emote prays aloud: More than any do I fear Thee, for Thou hast Eyes to see what comes, for you do stand at the edge of ruin, Vision of Ages");
      command("pray");
      break;
      case 17:
      command("emote traces his censer about the cryptic patterns upon the floor.");
      command("emote cries out: To the Twelve art we faithful, for we are the Ancient Order, abiding in Mystery, with Glory, Wisdom and Truth at our side");
      break;
      case 18:
      command("emote kneels down and prays.");
      command("emote kisses the floor.");
      if(ob) command("emote hands his censer to the acolyte.");
      ob->command("mnod cantor");
      break;
      default:
      remove_alarm(process);
      process = 0;
      command("emote traces and ancient sign before himself and solemnly proceeds to the temple.");
      command("e");
      if(ob) ob->command("e");
      ob->command("e");
      ob->command("n");
      ob->remove_object();
      command("e");
      TO->set_act_time(5);
   process = 0;
   remove_alarm(process);
      break;
   }
   time++;
   
}
te_deum(){
  object bone;
  object key;
  seteuid(getuid());
   switch(time){
  case 0: 
  TO->set_act_time(0);
  ob=clone_object("/d/Terel/mecien/valley/guild/lewen");
   ob->move_living("arrives", EN(TP));
 TO->command("say Dark is the hour... The time has come to honour the Holy Dead");
  TO->command("emote prays silently, seemingly in grief.");
  break;
  case 1:
   TO->command("e");
   ob->command("e");
   TO->command("e");
  ob->co("e");
   TO->command("d");
  ob->co("d");
    TO->command("emote kneels down and kisses the floor.");
    TO->command("say Oh mighty ones, I pray that thy rest has been peaceful, for I have not forgotten thee, no, not one of you");
   break;
  case 2:
  TO->command("say I pray for thee each day, to the Great Twelve, that they watch over you");
  key = clone_object("/d/Terel/mecien/valley/guild/crypt/ckey");
  key->move(TO);
   command("unlock gate with key");
  key->move(ob);
   ob->command("open gate");
   TO->command("say Forgive me, Watchers of the Dead, what I do is for their Glory, strike me not dead, so that each day I may continue to glorify them");
  TO->command("emote kneels down and prays silently.");
     break;
   case 3:
     command("emote gets a grim look upon his face.");
   command("w");
   ob->co("w");
   break;
    case 4: 
   co("say We have entered, ancient ones, I pray you forgive us, we are here for your glorification");
  break;
   case 5:
  co("say It is safe to proceed");
   co("emote prays silently.");
   ob->co("mnod cantor");
  break;
  case 6:
   co("w");
  ob->co("w");
   co("w");
  ob->co("w");
    break;
   case 7:
    co("emote looks at the different tombs and begins to weep.");
     co("say Though you do rest in Peace my aged friend, I do miss thee!");
   co("emote lays himself prostrate upon the floor.");
   ob->co("emote stands back in fear.");
   ob->co("say Holy Mieriys, let not death take you, we must glorify our brethren of the Past");
   break;
    case 8:
    co("emote stands tall and firm, imbued with some terrible spirit of majesty.");
  co("emote takes something forth a large crystal vial from his robes.");
  co("say Oh Ye Holy Dead, one day I shall join thee! For now I invoke the Twelve, that they visit you in your ancient slumber");
    co("emote prays.");
    co("emote sprinkles himself with water from the vial.");
   co("emote sprinkles the floor of the crypt with the vial.");
   break;
   case 9:
       command("remove robe");
        ob->co("emote assists Mieriys with his robe.");
   co("emote starts mumbling out ancient words, as if in some kind of trance.");
   break;
   case 10:
   co("drop robe");
   ob->co("emote folds the robe neatly on the ground.");
   co("shout AWAKE! AWAKE! Visit us Oh Ye Dead! For I wish to gaze upon Eternity within you!");
   ob->co("back");
    break;
   case 11:
   co("emote traces an ancient sign before himself.");
    co("say Where art thou? Most holy dead, I must now see thee");
  break;
     case 12:
   co("emote takes hold of one of the tombs.");
  co("say Bear witness Liyil and all Ye Mighty Virtues, for I Mieriys do now delve into the depths of Time itself and grasp at Eternity!");
    co("emote prays aloud a hymn of the dead.");
   ob->co("emote closes his eyes and turns away.");
  break;
   case 13:
    co("emote opens one of the tombs!");
      tell_room(EN(TO), "A horrible wind escapes from the tomb and fills this place! A sense of being watched falls upon you!\n");
   co("emote takes something from the tomb and closes it quickly.");
   break;
  case 14:
   bone = clone_object("/d/Terel/mecien/valley/guild/crypt/bone");
   co("emote holds aloft a ancient bone from one of the dead!");
  co("Here is Death! Here is Life! Here is the End and the Beginning! Here all things are made possible! For here is Eternity!");
   ob->command("dread");
   ob->co("weep");
  break;
  case 15:
   bone->move(EN(TO));
   co("emote lays the bone down upon his robe.");
   co("say Rest now upon my garment, for you are safe with us");
   co("say Fire of the East! I call upon Thy Sacred Mystery!");
   co("emote takes forth his censer.");
   co("emote rubs the censer with his hand.");
  break;
   case 16:
   co("say Come forth and burn once again within the Sleepers of Eternity!");
  co("emote prays over the censer.");
  break;
    case 17:
    tell_room(EN(TO), "The censer held by Mieriys grows hot and fiery, a burst of flame issues forth and descends upon the robe and bone, both consumed instantly!\n");
  bone->remove_object();
   tell_room(EN(TO), "The robe does not burn, but the bone fades into the fire.\n");
   break;
    case 18:
      tell_room(EN(TO), "You notice a strange cloud, dark and haunting shifting about the crypt, a figure within it, walking about, filled with fire.\n");
  co("emote kneels before the figure in the cloud saying: Hail Most Arcane Majesty");
   

  break;
   case 19:
  co("say Long has it been since I saw thee, Lord");
 co("emote prays silently.");
  break;
  case 20:
   tell_room(EN(TO), "The cloud seems to fade away.\n");
   co("say The Dead we do remember! For we of the Ancient Order are One, in Life, in Death, now and forever!");
   co("bow humbly");
   ob->co("bow humb");
      break;
   case 21:
  co("emote sprinkles water everywhere.");
   co("emote prays aloud, kneeling before the tombs.");
  co("say Rest in Peace, my brethren");
   co("emote kisses each of the tombs.");
   co("get robe");
  break;
   case 22:
   co("e");
  ob->co("e");
   co("e");
     ob->co("e");
   co("e");
     ob->co("e");
   break;
  case 23:
   co("sign");
   co("say I pray you keep them well, Watchers of the Dead");
   co("say The blessings of the Twelve reside here");
  break;
  case 24:
   co("pray");
   co("bow humb");
      co("wear robe");
   break;
   case 25:
  co("up");
  co("w");
  co("w");
    break;
  case 30:
  ob->co("close gate");
  ob->co("lock gate with key");
     co("up");
 ob->co("up");
   ob->co("w");
  ob->co("w");
   ob->co("n");
   ob->co("emote leaves.");
   ob->remove_object();
      TO->set_act_time(5);
   process = 0;
   remove_alarm(process);
      break;
   }
   time++;
   
}

public string
summon()
{
   object mon;
   
   seteuid(getuid());
   TO->command("emote traces a strange sign before himself " +
      "and speaks arcane words.");
   mon = clone_object(GUILD_DIR + "spells/angserp");
   mon->set_random_move(1, 1);
   mon->move_living("M", GUILD_DIR + "sanctuary");
   set_alarm(3.0, -1.0, "entre", mon);
   
   return "emote looks very serious.";
}

public void
entre(object mon)
{
   tell_room(ETO, "A green mist descends from the north.\n");
   mon->command("south");
   set_alarm(100.0, -1.0, "fade", mon);
}

public void
fade(object mon)
{
   if (!mon) return;
   tell_room(environment(mon), QCTNAME(mon) + " vanishes abruptly.\n");
   mon->remove_object();
}

public string
heal()
{
   tell_room(ETO, QCTNAME(TO) + " glows with a pale white light.\n", TO);
   heal_hp(300);
   return "msmile";
}

public string
word()
{
   object *all;
   int i;
   
   tell_room(ETO, QCTNAME(TO) + " chants an ancient word of " +
      "holiness!\n", TO);
   all = query_my_enemies();
   
   for (i=0; i<sizeof(all); i++) {
      all[i]->heal_hp(-100);
      if (all[i]->query_prop(LIVE_I_UNDEAD))
         all[i]->add_panic(200);
   }
   return "emote looks stern.";
}

public string
cant()
{
   object *all;
   int i;
   
   all = all_inventory(ETO);
   
   for (i=0; i<sizeof(all); i++) {
      if (!living(all[i])) continue;
      if (!MEMBER(all[i])) continue;
      if (all[i]->query_hp() < all[i]->query_max_hp())
         return "cantus";
   }
   
   return "emote intones an ancient song.";
}
