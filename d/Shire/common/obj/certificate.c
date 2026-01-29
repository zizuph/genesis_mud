/*
 *  The certificate that belongs to a pet.
 *  This one makes sure that the pet is reloaded at set to the right
 *  stats each time the player logs in.
 */
inherit "/std/object";

#include "defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/secure/std.h"

string dog_name, dog_race, dog_living_name, owner_name;
int dog_total_time, filled_in, *dog_stats;
int alarm_id;

/* Prototypes */
void check_present();
void lock_object();


void
create_object()
{
   set_name(({"certificate", "_pet_certificate_"}));
   set_pname("certificates");
   set_short("certificate of ownership");
   set_pshort("certificates of ownership");
   set_long("@@my_long");

   add_prop(OBJ_I_WEIGHT, 90);
   add_prop(OBJ_I_VOLUME, 90);
   filled_in = 0;
   dog_stats = ({ 8, 8, 8, 12, 12, 8 });
}

void
init()
{
   add_action("do_read","read");
   if (this_player() == environment(this_object())
    && this_player()->query_real_name() == owner_name)
   {
      if (!filled_in)
         add_action("do_fill","fill");
      else
         alarm_id = set_alarm(1.0,0.0,&check_present());
   }
}

string
query_auto_load()
{
   return MASTER_OB(this_object()) + ":" + dog_name + "**"
         + dog_race + "**" + dog_total_time + "*" + dog_stats[0] + "*"
         + dog_stats[1] + "*" + dog_stats[2] + "*" + dog_stats[3] + "*"
         + dog_stats[4] + "*" + dog_stats[5];
}

void
init_arg(string str)
{
   int i;

   if (str)
   {
      sscanf(str, "%s**%s**%d*%d*%d*%d*%d*%d*d", dog_name, dog_race,
             dog_total_time, dog_stats[0], dog_stats[1], dog_stats[2],
             dog_stats[3], dog_stats[4], dog_stats[5]);

      if (!dog_living_name)
      {
         /* Make up a unique living_name */
         i = 0;
         while(find_living(dog_living_name = ("_pet_" + dog_name + i)))
            i++;
      }
      filled_in = 1;
   }
   lock_object();
}

string
my_long()
{
   string the_long;

   the_long = "The certificate says that you, "
    + capitalize(owner_name) + ", are the rightful "
    + "owner of "
    + (filled_in ? capitalize(dog_name) : "........")
    + " the " + dog_race + ". "
    + "The ownership is void when the obligations as stated in the "
    + "brochure are no longer fulfilled.\n";

   return break_string(the_long, 70);  
}

void
check_present()
{
   object pet;

   seteuid(getuid());

   remove_alarm(alarm_id);
   if (dog_living_name && !find_living(dog_living_name))
   {
     pet = clone_object("/d/Shire/dunstable/pet");
      pet->set_my_name(dog_name);		  /* Set the new name     */
      pet->set_living_name(dog_living_name);      /* Unique living_name   */
      pet->set_race_name(dog_race);               /* The dog's race       */
      pet->set_total_time(dog_total_time);        /* Time since last feed */
      pet->set_owner(owner_name);
      pet->set_stats(dog_stats);
      pet->move(environment(environment()));
   }
}

void
set_dog_name(string str)
{
   int i;

   dog_name = str;

   /* Make up a unique living_name */
   i = 0;
   while(find_living(dog_living_name = ("_pet_" + dog_name + i)))
      i++;
}

void
set_owner_name(string str)
{
   owner_name = str;
}

void
set_dog_race(string str)
{
   dog_race = str;
}

void
set_dog_total_time(int time)
{
   dog_total_time = time;
}

/*
 * Make sure the certificate doesn't run away.
 */
void
lock_object()
{
   add_prop(OBJ_I_NO_GET, 1);
   add_prop(OBJ_I_NO_INS, 1);
   add_prop(OBJ_I_NO_GIVE, 1);
   add_prop(OBJ_I_NO_DROP, 1);
}

int
do_fill(string str)
{
   string tmp, tmp2;

   if (!str || filled_in)
      return 0;

   if (!sscanf(str, "in %s", tmp))
   {
      notify_fail("Fill in what name?\n");
      return 0;
   }
   str = lower_case(tmp);
   if (strlen(str) > 12)
   {
      write("That name is too long to fill in.\n");
      return 1;
   }

   if (sscanf(str, "%s %s", tmp, tmp2) == 2)
   {
      write("You may only fill in single names.\n");
      return 1;
   }

   set_dog_name(str);
   filled_in = 1;
   write("You fill in " + capitalize(str) + " for the " + dog_race
       + "'s name.\n");
   say(QCTNAME(this_player())+" scribbles something on the certificate.\n");
   check_present();
   return 1;
}

int
do_read(string str) {
   if (str == "certificate" || str == "certificate of ownership")
   {
      write(my_long());
      return 1;
   }
   notify_fail("Read what?\n");
   return 0;
}
