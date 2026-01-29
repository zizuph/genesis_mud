#pragma save_binary


/* Help handler file for Bubba the blacksmith in Gelan.

   Coded by Maniac 27.6.95
   Switched to regular <more>, Maniac, 10/6/96 
*/


void
general_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_DIR + "bubba_general.txt"));
}


void
armour_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_DIR + "armour.txt"));
}


void
polearm_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_DIR + "polearm.txt"));
}

void
repairs_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_DIR + "repairs.txt"));
}

void
paying_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_DIR + "paying.txt"));
}

int
do_help(string str)
{
    string s;
    object tp = this_player();

    if (!str)
        return 0;

    if (str == "bubba") {
        general_help();
        return 1;
    }

    if (sscanf(str, "bubba %s", s) == 1) {
        switch (s) {
            case "repairs" :
                      repairs_help();
                      return 1;
                      break;
            case "armour" :
                      armour_help();
                      return 1;
                      break;
            case "polearms" :
                      polearm_help();
                      return 1;
                      break;
            case "paying" :
                      paying_help();
                      return 1;
                      break;
            default :
                      tp->catch_msg("No such Bubba help option.\n");
                      return 1;
                      break;
        } 
    }
}
