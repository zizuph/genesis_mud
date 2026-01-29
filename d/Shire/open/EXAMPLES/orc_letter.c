inherit "std/object";

#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"

int wise,questnr;
/* Prototypes */
string my_long();

/*
 * Function name: create_object
 * Description:   The standard create
 */
void
create_object()
{
    set_name("letter");
    set_adj("dirty");
    add_name("_orc_letter_");
    set_short("@@my_short");
    set_long("@@my_long");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);

    wise = 0;
    questnr = 111;
}

void init()
{
    ::init();

    add_action("do_read", "read");
}



int do_read()
{
    write(my_long());
    return 1;
}


/* Function name: my_short
 * Description:   Get a short description
 * Returns:       The short description
 */
string
my_short()
{
    string short;

    if(!wise)
      short = "dirty letter";
    else
      short = "neat letter";

    return short;
}

/* Function name: my_long
 * Description:   Get a long description
 * Returns:       The long description
 */
string
my_long()
{
  string long;

  if(!wise) {
    if(this_player()->query_skill(SS_LANGUAGE) < 15) {
      long = "The letter is written in a language unknown to you.\n";
      long += "It looks like some orders to the orcs.\n";
      long += "Maybe you should inform someone about it.\n";
      return long;
    }

    if(this_player()->query_skill(SS_LANGUAGE) < 30)    {
      long = "The letter is written in orcish.\n" +
	"It looks like some orders to the orcs.\n"
	  + "Maybe you should inform someone about it.\n";
      return long;
    }
    long = "The letter is written in orcish. You can make out the words\n"
      + "'Shire', 'army' and 'boat'.\n";
    long += "It looks like some orders to the orcs.\n";
    long += "Maybe you should inform someone about it.\n";
    return long;

  }
  else {
    long = "The letter is a translation from an orc letter made by\n"
      + "Raston. It is an order to the orcs to invade the Shire area\n"
      + "and to destroy Hobbiton. The orcs are supposed to make rafts\n"
	   + "and sail down the Brandywine, then follow Eastroad to "
	   + "hobbiton.\n";
  }
  return long;
}

/*
 * Function name: are_u_quest_letter()
 * Description:   returns 666 to tell that this is the right letter
 */
int are_u_quest_letter() {
  return questnr;
}

/*
 * Function name: make_wise
 * Description:   makes this a translation of the original letter.
 */
make_wise() {
  wise = 1;
  set_name("letter");
  set_adj("neat");
  set_short("@@my_short");
  set_long("@@my_long");
  questnr = 222;
}
