/*
 * In this file there are defined functions that select herbs and sites
 * for Smaug quest in Esgaroth. The following calls will give you result:
 *     "name_of_this_file"->select_herbs("name_of_player");
 *     "name_of_this_file"->select_sites("name_of_player");
 *
 *  Milan  7.2.95
 */

#define SITES ({ "/d/Rhovanion/milan/workroom", \
                 "0", \
                 "1", \
                 "2", \
                 "3", \
              })
#define HERBS ({ "acorn","aulare","baldae","belakin","belienthas","bella", \
                 "bolishno","caltire","cloe","gadiem","gailish","galianth",\
                 "herkin","jilkin","khazad","khuz","kilant","laranatha",   \
                 "linthor","mallea","maroea","myntha","peliana","pinotta", \
                 "porin","riketh","silfa","tarlek","taurin","uildar",      \
                 "vilithin","waternut","welkinth","ylivath"                \
              })

/*
 * Function name: select_herbs
 * Argument:      name - string
 * Description  : returns list of herbs for given name
 */
string *select_herbs(string name)
{
  string *herbs = HERBS;
  string h, *hhh = ({ });
  int i, seed, l = strlen(name);

  if(!l) return hhh;   /*  wrong parameter name  */

  for(i=0; i<l; i++)
    seed += name[i];  /* now we have basic seed */
  for(i=0; i<5; i++)
  {
    seed += name[i % l];
    h = herbs[ random(sizeof(herbs), seed) ];
    hhh += ({ h });
    herbs -= ({ h });
  }
  return hhh;
}

/*
 * Function name: select_sites
 * Argument:      name - string
 * Description  : returns list of sites for given name
 */
string *select_sites(string name)
{
  string *sites = SITES;
  string s, *sss = ({ });
  int i, seed, l = strlen(name);

  if(!l) return sss;   /*  wrong parameter name  */

  for(i=0; i<l; i++)
    seed += name[i];  /* now we have basic seed */
  seed /= 2;          /* change it a bit from herb seed */
  for(i=0; i<5; i++)
  {
    seed += name[i % l];
    s = sites[ random(sizeof(sites), seed) ];
    sss += ({ s });
    sites -= ({ s });
  }
  return sss;
}
