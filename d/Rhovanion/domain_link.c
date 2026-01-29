inherit "/std/domain_link";

void add_preload(string s) { preload(s); }

void preload_link()
{
	/* Ships from Rhun to Esgaroth, and Rhun to Emerald */
	add_preload("/d/Rhovanion/common/rhun/stown3/pier1");
	add_preload("/d/Rhovanion/common/rhun/stown3/pier2");

	/* Ferry boat from ltown_ne to ltown_sw in Rhun */
	add_preload("/d/Rhovanion/common/rhun/ltown_ne/streets/dock");

        /* Title object for Angmar's army */
        add_preload("/d/Rhovanion/common/shield_guild/s_c_titles");
}
