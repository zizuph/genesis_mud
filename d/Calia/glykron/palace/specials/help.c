#pragma save_binary

/* Code that is included into the calian_cmdsoul to handle the 
   informative help options that are offered to players. 

   Coded by Maniac

   History:
        29/10/96    medallion option added          Maniac
         6/10/96    battle option added             Maniac
         18/9/96    coptions added                  Maniac
         20/6/96    updated for regular <more>      Maniac
         27.12.95   ctitle option added             Maniac
         21.12.95   rack option added               Maniac
         17.5.95    caliana help option added       Maniac
          7.4.95    applicants help option added    Maniac 
         28.3.95           created                  Maniac
*/

#define HELP_FILE_DIR "/d/Calia/glykron/palace/texts/"


void
general_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "general_help"));
}


void
medallion_help()
{
    string *mt; 

    mt = MEDALLION_TINTS; 
    setuid(); 
    seteuid(getuid()); 
    this_player()->more(read_file(HELP_FILE_DIR + "medallion") + 
                 "\nThe progression of tints for your medallion " + 
                 "is as follows:\n" + 
                 break_string(COMPOSITE_WORDS(mt), 70) + ".\n"); 
}


void
kroug_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "kroug"));
}


void
caliana_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "caliana"));
}

void
battle_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "battle"));
}

void
council_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(COUNCIL_CODE->query_council() + 
                   read_file(HELP_FILE_DIR + "council"));
}


void
rules_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "rules"));
}


void
roff_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(RECRUITER_CODE->query_recruiters_string() + 
                        read_file(HELP_FILE_DIR + "officers"));
}


void
app_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(RECRUITER_CODE->query_applicants_string() + 
                     "\n" + RECRUITER_CODE->query_accepted_string() + 
                     read_file(HELP_FILE_DIR + "applicants"));
}


void
enemies_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(COUNCIL_CODE->query_enemies() + 
                        read_file(HELP_FILE_DIR + "enemies"));
}


void
emotes_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "emotes"));
}



void
calian_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "calian"));
}


void
commands_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "commands"));
}

void
coptions_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "coptions"));
}

void
rack_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "rack"));
}


void
ctitle_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(CALIAN_TITLE_HANDLER->query_el_desc() + 
                        read_file(HELP_FILE_DIR + "ctitle"));
}


void
fail_help()
{
    this_player()->catch_msg("There is no such Calian help option.\n");
}


int
help(string str)
{
    string s;

    if (!str) return 0;

    if (str == "calian") {
        general_help();
        return 1;
    }

    if (sscanf(str, "calian %s", s) == 1) {
        switch (s) {
            case "medallion" : 
                            medallion_help();  
                            break;
            case "battle" : battle_help(); 
                            break;
            case "caliana" : caliana_help();
                             break;
            case "kroug" : kroug_help();
                           break;
            case "council" : council_help();
                             break;
            case "calian" : calian_help(); 
                              break;
            case "coptions" : coptions_help(); 
                              break;
            case "rules" : rules_help();
                           break;
            case "officers" : roff_help();
                              break;
            case "applicants" : app_help();
                              break;
            case "enemies" : enemies_help();
                             break;
            case "emotes" : emotes_help();
                            break;
            case "commands" : commands_help();
                              break;
            case "rack" : rack_help();
                          break;
            case "ctitle" : ctitle_help();
                            break;
            default : fail_help();
                      break;
        }
       return 1;
    }
    return 0;
}


