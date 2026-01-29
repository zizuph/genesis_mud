// file name:    ~Avenir/inherit/sigil
// creator(s):   Lucius, 02 July 2006
// purpose:      An inheritable file to provide a simple way to
//       retrieve sigil information for Sybarun Houses.
// notes:        Information originally obtained from:
//               ~Avenir/doc/social/houses.heraldry
// to-do:
// last update:
#pragma no_clone
#pragma strict_types

#define OBJECT "/d/Avenir/common/obj/sigil"

#define HOUSE_SIGIL    0
#define HOUSE_BORDER   1

/*
 * The mapping of sigils, by House name.
 *
 *    HOUSE :
 *	SIGIL / ESCUTCHEON,
 *	BORDER,
 */
private static mapping sigils = ([
  "Abun'ana"  : ({
	"a gold brazier on a field of blue",
	"purple", }),
  "Ardura"    : ({
	"a slender dagger, point down, on a field of orange and gold chequers",
	"crimson", }),
  "Adayr"     : ({
	"an ivory talon on a field of cerulean",
	"purple", }),
  "Arn'siri"  : ({
	"a silver war-axe on a field of yellow",
	"green", }),
  "Atrei"     : ({
	"blue and yellow chequers",
	"crimson", }),
  "Cha'uri"   : ({
	"a twelve pointed silver star on black",
	"crimson", }),
  "Charna"    : ({
	"a shaggy goat on a field of grey",
	"purple", }),
  "Cimron"    : ({
	"a white cygnet on a field of blue",
	"crimson", }),
  "Contrae'ree" : ({
	"a circlet made of twisted thorn banches",
	"green", }),
  "Dor'as"    : ({
	"a grey dove & black flail on yellow",
	"crimson", }),
  "Ebonast"   : ({
	"a black spider on a field of white",
	"crimson", }),
  "Fatin"     : ({
	"five red droplets on a field of gold",
	"purple", }),
  "Fil'kaag"  : ({
	"an iron-mailed fist on a field of gold",
	"purple", }),
  "F'niel"    : ({
      "a gold cup on a field of orange",
	"green", }),
  "Frona"     : ({
	"a bloody dagger on a field of white",
	"crimson", }),
  "G'tril"    : ({
	"a winged wolf on a field of black",
	"green", }),
  "Hayz"      : ({
	"a silver triskelion on a field of black",
	"green", }),
  "Hu'garen"  : ({
	"a copper abacus on a field of brown",
	"purple", }),
  "Imsa-sa"   : ({
	"white and blue diagonal stripes",
	"crimson", }),
  "I'orar"    : ({
	"a flaming kesoit branch on a field of white",
	"crimson", }),
  "L'derac"   : ({
	"a green aglyna on a field of black",
	"purple", }),
  "Ler'iss"   : ({
	"a black panther on a field of gold",
	"green", }),
  "Llin"      : ({
	"a black lily on a field of yellow",
	"crimson", }),
  "Lochnir"   : ({
	"a kesoit branch on a field of blue",
	"green", }),
  "Malefic"   : ({
	"a silver barb on a field of black",
	"green", }),
  "Mindorn"   : ({
	"a silver serpent, coiled, on black and white chequers",
	"purple", }),
  "Mort"      : ({
	"a black skull on a field of white",
	"crimson", }),
  "Nereza"    : ({
	"a silver rose on a field of grey",
	"purple", }),
  "Ni'stu"    : ({
	"a wreath of nightshade on a field of blue",
	"green", }),
  "Nys'it"    : ({
	"a pair of aglyna wings on a field of silver",
	"crimson", }),
  "Primdel"   : ({
	"a brown quarterstaff on a field of orange",
	"green", }),
  "Qasz"      : ({
	"a white crescent on a field of black",
	"purple", }),
  "Ra'let"    : ({
	"a fire lizard on a field of black",
	"green", }),
  "Ramar"     : ({
	"a bloodwood tree on a field of gold",
	"crimson", }),
  "Rinsil"    : ({
	"silver and blue chequers",
	"purple", }),
  "R'yis"     : ({
	"a white quill on a field of brown",
	"green", }),
  "S'hu"      : ({
	"a violet sea serpent on a field of grey",
	"green", }),
  "Sindri"    : ({
	"three black chains on a field of white",
	"purple", }),
  "Sisaer"    : ({
	"a wand and scourge on a field of blue",
	"purple", }),
  "Ummus"     : ({
	"a white pentacle on a field of black",
	"crimson", }),
  "Tirisi"    : ({
	"three stone columns on a field of blue",
	"purple", }),
  "Teivel"    : ({
	"a coiled brown leather whip on a field of yellow",
	"green", }),
  "Tor-loral" : ({
	"a golden goat on field of white",
	"purple", }),
  "Vyis"      : ({
	"a gold cat on a field of brown",
	"green", }),
  "Wer'a"     : ({
	"a blue flame on a field of white",
	"green", }),
  "Xisis"     : ({
	"twelve red drops on a field of yellow",
	"crimson", }),
  "Zel'ani"   : ({
	"a powerful bicorn on a field of black",
	"purple", }),
  "Zillah"    : ({
	"a bow with a flaming arrow on a field of grey",
	"crimson", }),
]);

private static mapping affil = ([
  "green"    : "Inquisitor",
  "purple"   : "Commisioner",
  "crimson"  : "Executioner",
]);


public static string my_house = "", my_sigil = "", sigil_text = "";

/**************************************************************************
 ******   General usage query functions   *********************************
 **************************************************************************/

/*
 * Returns an array of known Sybarun Houses.
 */
public string *
query_syb_houses(void)
{
    return m_indexes(sigils);
}

/*
 * Returns the array info for a Sybarun House.
 */
public string *
query_syb_house(string house)
{
    string *arr;

    if (strlen(house))
	house = capitalize(house);
    else
	return ({});

    if (sizeof(arr = sigils[house]))
	return secure_var(arr);
    else
	return ({});
}

/*
 * Returns the High Lord affiliation for a given
 * House or sigil-border.
 */
public string
query_syb_affiliate(string arg)
{
    string str;

    if (!strlen(arg))
	return "";

    if (strlen(str = affil[arg]))
	return str;

    arg = capitalize(arg);

    if (!sizeof(sigils[arg]))
	return "";

    if (strlen(str = affil[sigils[arg][HOUSE_BORDER]]))
	return str;
    else
	return "";
}

/*
 * Returns the sigil for a given house.
 */
public string
query_sigil(string house)
{
    string *arr;

    if (strlen(house))
	house = capitalize(house);
    else
	return "";

    if (sizeof(arr = sigils[house]))
	return arr[HOUSE_SIGIL];
    else
	return "";
}

/*
 * Returns the sigil border for a house (affiliation).
 */
public string
query_sigil_border(string house)
{
    string *arr;

    if (strlen(house))
	house = capitalize(house);
    else
	return "";

    if (sizeof(arr = sigils[house]))
	return arr[HOUSE_BORDER];
    else
	return "";
}

/*
 * Return a Sybarun House for a given sigil.
 */
public string
query_sigil_house(string str)
{
    if (!strlen(str))
	return "";

    foreach(string house, string *arr : sigils)
    {
	if (str == arr[HOUSE_SIGIL])
	    return house;
    }

    return "";
}

/**************************************************************************
 ******   Object/NPC set/query functions   ********************************
 **************************************************************************/

/*
 * Setup our house & sigil.
 * Set 'noclone' if you don't want the sigil object cloned.
 */
static varargs void
set_syb_house(string str, int noclone)
{
    if (!strlen(str))
    {
	my_house = one_of_list(m_indexes(sigils));
    }
    else
    {
	str = capitalize(str);

	if (!sizeof(sigils[str]))
	{
	    my_house = "";
	    my_sigil = "";
	    sigil_text = "";
	    return;
	}

	my_house = str;
    }

    my_sigil = sigils[my_house][HOUSE_SIGIL];
    sigil_text = my_sigil + ", bordered in " +
	sigils[my_house][HOUSE_BORDER];

    if (noclone)
	return;

    object ob = clone_object(OBJECT);
    ob->move(this_object());
    ob->make_sigil("random");
}

/*
 * Query our chosen Sybarun House.
 */
public string
query_my_house(void)
{
    return my_house;
}

/*
 * Query the sigil of our Sybarun House.
 */
public string
query_my_sigil(void)
{
    return my_sigil;
}

/*
 * Full textform for either our sigil, or a given house.
 */
public varargs string
query_sigil_text(string str)
{
    string *arr;

    if (!strlen(str))
    {
	if (strlen(sigil_text))
	    return sigil_text;
	else
	    return "";
    }

    str = capitalize(str);

    if (!sizeof(arr = sigils[str]))
	return "";

    return arr[HOUSE_SIGIL] +", bordered in "+ arr[HOUSE_BORDER];
}
