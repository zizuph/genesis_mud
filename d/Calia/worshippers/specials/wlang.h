/* 
 * Code for the Worshippers Chant Language
 *   Sir Jaacar, 051396
 * Based on the Language of the Union of the
 * Warriors of Shadow.
 *   Lord Cirion, 032696
 * Thanks Cirion!  I appreciate the loan of the language!
 */

#ifndef MY
#define MY this_player()->query_possessive()
#endif
#define HE this_player()->query_pronoun()
#define SPIRIT_GUILD "Spirit Circle of Psuchae"

#define W1 ({ "a", "o", "t", "i", "z", "b", "j", \
               "d", "e", "f", "g","h","l","m","n","p", \
               "r", "s", "u", "v","w","x","y","z", \
              "c", "k", "q" })
#define W2 ({ "om", "if", "ch", "am", "re", "mi'", \
               "bl","ql","oi","as","ma","no","ya", \
              "or", "it", "bo", "ak", "to", "la" })
#define W3 ({ "ahm", "and", "omy", "doh", "cah", "ter", \
              "kip", \
              "fla","rao","bre","arl","the","dcy","qll" })
#define W4 ({ "aril", "snay", "they", "krou", "flet", \
              "nkef", "wual", \
              "wutm", "mini", "toub", "unpi", "ogrk", "ueld", \
              "nbyk", "yday", "nknn", "tsio", "sioc", "dodm", \
              "ques", "land", "ordi", "ther" })
#define W5 ({ "floor", "forgt", "amlis", "agnis", "print", \
              "oldia", "rattu", "emmig", "tornu", "lestl", \
              "jrahv", "qlljo", "fwifv", "wimpk", "biann", \
              "cooqt", "tuhin", "difwq", "wqepe", "itfun", \
              "funsf", "nsfac", "ipgmu", "mucre", "ilbev", \
              "xemia", "dolbe", "rsqev", "ypilo", "tadex", \
              "bevse", "cuvie", "viewa", \
              "tanli", "otrile", "nessu", "kilas", "shyly" })
#define W6 ({ "questi", "ahmnis", "lyinle", "kmiasl", \
              "ccuojl", "nwoonj", "rlymdy", "xnsiwc", "tleenk", \
              "bpaldi", "exuocy", "jactod", "todeus", "maxliv", \
              "nalyia", "wytlge" })


/*
 * Function:   replace
 * Arguments:  one word to replace
 * Returns:    A replacement word of the same
 *             string length in the new language.
 * Assuming it works, it works something like this:
 * The string 'What is happening? I thought Cirion was coming!
 * would be translated to
 *         'Aril t'r agrnis? O quelit Cirion rei lyinle!'
 */
string replace(string str)
{
  string back, nihil;

  switch(strlen(str))
  {
    case 1: back = W1[random(sizeof(W1))]; break;
    case 2: back = W2[random(sizeof(W2))]; break;
    case 3: back = W3[random(sizeof(W3))]; break;
    case 4: back = W4[random(sizeof(W4))]; break;
    case 5: back = W5[random(sizeof(W5))]; break;
    default: back = W6[random(sizeof(W6))]; break;
  }

  /* Retain names of living people */
  if(stringp(str) && find_living(lower_case(str)))
    back = CAP(str);

  /* Retain capitializations */
  if(str == CAP(str))
   back = CAP(back);

  /* Retain punctuation */
  if(sscanf(str, "%s.", nihil))
   back += ".";
  if(sscanf(str, "%s!", nihil))
   back += "!";
  if(sscanf(str, "%s?", nihil))
   back += "?";
  if(sscanf(str, "%s,", nihil))
   back += ",";

  return back;
}

/*
 * Function: construct_str
 * Argument: the array of words to be replaced into
 *           the new language.
 * Returns:  The array of words in the translated
 *           string.
 */
string *construct_str(string *oldstr)
{
   string *newstr;
   int     i;

  for(i=0; i<sizeof(oldstr); i++)
     newstr[i] = replace(oldstr[i]);

  return newstr;
}

void usay_to(object me, object who, string *newstr, string *oldstr, string what)
{
  int      lang,
           i;
  string   endstr = "";

  if(!present(who, ENV(me)))
    return;

  /* Members automatically understand it */
  if(IS_MEMBER(who))
  {
    who->catch_msg(QCTNAME(me)+" chants in the Ancient Mantras: "
      +what+"\n");
    return;
  }

  if (who->query_guild_name_occ() == SPIRIT_GUILD)
  {
      who->catch_msg(QCTNAME(me)+" chants in the Ancient Mantras: "
        +what+"\n");
      return;  
  }
    /* Wizards automatically understand it */
    if (who->query_wiz_level())
    {
        who->catch_msg(QCTNAME(me)+" chants in the Ancient Mantras (which you understand because you "+
            "are a wizard): "+
            what+"\n");
        return;
    }

  lang = who->query_skill(SS_LANGUAGE);

  if(lang < 25)
  {
    for(i=0;i<sizeof(newstr);i++)
     endstr += newstr[i] + " ";
    who->catch_msg(QCTNAME(me)+" chants in strange "
     +"mantras: "+endstr+"\n");
    return;
  }

  if(lang < 50)
  {
    for(i=0;i<sizeof(newstr);i++)
     endstr += newstr[i] + " ";
    who->catch_msg(QCTNAME(me)+" chants in a "
     + "language you recognize as ancient mantras: "+endstr+"\n");
    return;
  }

  for(i=0;i<sizeof(newstr);i++)
  {
    if((lang + random(20)) > random (175))
      endstr += oldstr[i] + " ";
    else
      endstr += newstr[i] + " ";
  }

  who->catch_msg(QCTNAME(me)+" chants in a "
     +"language you recognize as the Elemental Mantras: "+endstr+"\n");
  return;
}

int usay(string str)
{
  object  *people;
  mixed    fail_msg;
  int      i, who;
  string  *oldstr,
          *newstr;

    who = TP->query_skill(SS_PATRON_ELEMENTAL);

    if (!strlen(str) || str == "")
    {
        switch (who)
        {
            case FIRE_FLAG:
                write("You sit briefly and chant in the sounds of a "+
                    "crackling flame.\n");
                all(" sits down and begins to chant.\nYou hear the "+
                    "sound of crackling flames in "+MY+" voice.  After a brief "+
                    "moment, "+HE+" rises again.");
                break;
            case EARTH_FLAG:
                write("You sit briefly and chant in the sounds of the "+
                    "pounding earth.\n");
                all(" sits down and begins to chant.\nYou hear sounds "+
                    "like that of the pounding earth in "+MY+" voice.  "+
                    "After a brief moment, "+HE+" rises again.");
                break;
            case WATER_FLAG:
                write("You sit briefly and chant in the sounds of the "+
                    "ocean waves.\n");
                all(" sits down and begins to chant.\nYou hear the "+
                    "sound of the ocean in "+MY+" voice.  After a brief "+
                    "moment, "+HE+" rises again.");
                break;
            default:
                write("You sit briefly and chant in the sounds of the "+
                    "howling winds.\n");
                all(" sits down and begins to chant.\nYou hear the "+
                    "sounds of the howling winds in "+MY+" voice.  "+
                    "After a brief moment, "+HE+" rises again.");
                break;
        }
        return 1;
    }    
    
  NF("You do not have enough skill yet to use the Elemental Mantras.\n");
  if(TP->query_skill(SS_LANGUAGE) < 15)
    return 0;

  if(fail_msg = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
  {
//    if(stringp(fail_msg))
//     NF(fail_msg);
//    else
     NF("You cannot seem to use your mouth.\n");
    return 0;
   }

  people = filter(all_inventory(ENV(TP)), interactive) - ({ TP });
  
    if (TP->query_option(OPT_ECHO))
    TP->catch_msg("You chant in the Ancient Mantras: "+str+"\n");
  else
    TP->catch_msg("Ok.\n");

  if(!sizeof(people))
   return 1;

  oldstr = explode(str, " ");

  newstr = allocate(sizeof(oldstr));

  for(i=0; i<sizeof(oldstr); i++)
     newstr[i] = replace(oldstr[i]);

  for(i=0;i<sizeof(people);i++)
    usay_to(TP, people[i], newstr, oldstr, str);

  return 1;
}
