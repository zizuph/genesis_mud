/* A file which can be used to save some time when using
 * randomness, such as generating npc's with random
 * names.
 * Damaris 5/2001
 *
 */
#pragma strict_types

#include "/d/Genesis/login/login.h"
private string query_male_name();
private string query_female_name();
private string query_hcolour();
private string query_ecolour();
private string query_ftitles();
private string query_mtitles();
private string query_skin();
private string query_body1();
private string query_body2();
private string query_race1_name();
string _MNAME = query_male_name();
string _FNAME = query_female_name();
string _HCLR = query_hcolour();
string _ECLR = query_ecolour();
string _FTITLE = query_ftitles();
string _MTITLE = query_mtitles();
string _SKIN = query_skin();
string _BODY1 = query_body1();
string _BODY2 = query_body2();
string _RACE = query_race1_name();

private string
query_race1_name()
{
  string *race1_name = ({
        "elf", "human",
                    });
  return race1_name[random(sizeof(race1_name))];
}
private string
query_male_name()
{
  string *names = ({
        "aaron", "abbott", "abel", "abijah", "abner", "abram",
	"adin", "axel", "ari", "barth", "ben", "boaz", "caleb",
	"calvin", "daniel", "datan", "david", "demetrius", "devir",
	"efrem", "ellis", "enoch", "eran", "ezri", "gad", "gilad",
	"hadar", "ian", "imri", "james", "jethro", "job", "john",
	"joseph", "jude", "kalil", "kedar", "kenan", "laban", "lucas",
	"luke", "micah", "michael", "miles", "nemuel", "omar", "ofir",
	"paul", "rami", "ron", "seth", "shem", "stephen", "tamir",
	"tilon", "tobias", "victor", "xavier", "yagil", "zeke",
                        });

  return names[random(sizeof(names))];
}
private string
query_female_name()
{
  string *names = ({
        "abra", "adie", "adra", "ariza", "arza", "becca", "berit", 
        "beth", "bethany", "bina", "chloe", "dalia", "dani", "dara",
        "debora", "diana", "dodi", "elana", "elza", "esther", "eva",
        "gada", "gali", "geva", "gina", "hadass", "hilla", "ilana",
        "iris", "jaime", "jane", "janice", "jemini", "jesse", "jodie",
        "judith", "kayla", "kathrine", "leah", "libby", "lois", "lydia",
        "madeline", "madya", "mary", "nancy", "neah", "nina", "oprah",
        "phoebe", "rana", "rena", "rhoda", "ruth", "shaina", "sharai",
        "sima", "tabitha", "talia", "tamara", "tori", "uma", "vanessa",
        "veronica",
                   });

  return names[random(sizeof(names))];
}
private string
query_ftitles()
{
  string *ftitles = ({
        "concubine of Alexander", "devotee of Alexander",
        "concubine of Dedrick", "devotee of Dedrick",
        "concubine of Fullwood", "devotee of Fullwood",
        "concubine of Haken", "devotee of Haken",
        "concubine of Kirkland", "devotee of Kirkland",
        "concubine of Lakin", "devotee of Lakin",
        "concubine of Maddox", "devotee of Maddox",
        "concubine of Neve", "devotee of Neve",
                        });

  return ftitles[random(sizeof(ftitles))];
}
private string
query_mtitles()
{
  string *mtitles = ({
        "servant of Alexander", "disciple of Alexander",
        "servant of Dedrick", "disciple of Dedrick",
        "servant of Fullwood", "disciple of Fullwood",
        "servant of Haken", "disciple of Haken",
        "servant of Kirkland", "disciple of Kirkland",
        "servant of Lakin", "disciple of Lakin",
        "servant of Maddox", "disciple of Maddox",
        "servant of Neve", "disciple of Neve",
                        });

  return mtitles[random(sizeof(mtitles))];
}

private string
query_hcolour()
{
  string *hcolour = ({
        "black", "brown", "red", "sandy", "blonde", "red flame",
        "silvery", "soft brown", "redish brown", "platinum blonde",
        "jet black", "raven black", "chestnut brown",
                     });
  return hcolour[random(sizeof(hcolour))];
}

private string
query_ecolour()
{
  string *ecolour = ({
        "coal black", "sparkling blue", "sky blue", "dark brown",
        "crystal blue", "emerald green", "forest green", "soft brown",
        "deep brown", "green",
                    });
  return ecolour[random(sizeof(ecolour))];
}

private string
query_skin()
{
  string *skin = ({
        "smooth ebony", "sultry black", "milk white", "warm brown",
        "sun tanned", "succulent peach", "shimmering white",
        "lustrious white", "pale white", "light brown",
                 });
  return skin[random(sizeof(skin))];
}

private string
query_body1()
{
    string *body1 = ({
      "blood-craving", "captivating", "clean", "calm", 
      "dangerous","determined", "dirty", "disheveled",
      "disfigured", "elusive", "foul-looking", "foul-smelling",
      "friendly", "grim", "honest", "humble", "hypnotic", "impressive",
      "innovative", "irritable", "lanky", "leathery", "meek", 
      "muscular", "musky", "mysterious", "prim", "scarred", "sinewy",
      "slouchy", "slovenly", "smooth-skinned", "strange", "sweaty",
      "tidy-looking", "unkempt", "well-groomed", "wrinkled",
      "big-shouldered", "broad-shouldered", "shrug-shouldered",
      "heavy", "lean", "light", "skinny", "slender", "slight",
      "slim", "small", "stocky", "stout", "thin", "tiny",
      "small-shouldered", "wide-shouldered", "slender-shouldered", 
                     });
    return body1[random(sizeof(body1))];
}

private string
query_body2()
{
    string *body2 = ({
      "bent-nosed", "big-nosed", "bulbous-nosed", "flat-nosed",
      "hawkish-nosed", "hook-nosed", "knob-nosed", "pointy-nosed",
      "pug-nosed", "red-nosed", "wart-nosed", "upnosed",
      "buck-toothed", "gap-toothed", "purse-lipped",
      "square-jawed", "tight-jawed", "wide-mouthed",      
      "big-fingered", "bony-fingered", "fat-fingered",
      "flat-fingered", "gaunt-fingered", "grimy-fingered",
      "lean-fingered", "long-fingered", "narrow-fingered",
      "nimble-fingered", "pudgy-fingered", "quick-fingered",
      "round-fingered", "short-fingered", "skeletal-fingered",
      "slender-fingered", "slimy-fingered", "small-fingered",
      "stubby-fingered", "thin-fingered",
      "blemished", "bony-cheeked", "bony-faced", "chinless",
      "double-chinned", "dimpled", "flat-chinned", "freckle-faced",
      "jug-eared", "jut-jawed", "long-faced", "oval-faced", "square-faced",
      "red-cheeked", "round-faced", "slope-browed", "stone-faced",
      "thin-faced", "adolescent", "ageless", "ancient", "mature",
      "middle-aged", "timeworn", "venerable", "young",
                     });
    return body2[random(sizeof(body2))];
}
