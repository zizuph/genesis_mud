/*
 *  /d/Gondor/guilds/morgulmage/master/options.c
 *
 *  This file is part of the Morgul Mage master object. It should
 *  not be loaded or called directly.
 *
 *  Created by Eowul, June 30th, 2009
 */
 
/*
 * Function   : set_mage_option
 * Description: Store an option value for the mage
 * Arguments  : mixed mage - the mage to set the option for
 *            : string option - the name of the option
 *            : mixed value -  the value of the option
 */
public void set_mage_option(mixed mage, string option, mixed value) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);

    if(member_array("option", m_indices(member_information[magename])) == -1) {
        member_information[magename]["option"] = ([ ]);
    }
    
    member_information[magename]["option"][option] = value;
    save_data();
}

/*
 * Function   : get_mage_option
 * Description: Returns the option value stored for the mage
 * Arguments  : mixed mage - the mage to get the option for
 *            : string option - the name of the option
 *            : mixed optiondefault - the default to return when no value is stored
 * Returns    : The value of the option or the default
 */
mixed get_mage_option(mixed mage, string option, mixed optiondefault = 999) {
    string magename = get_mage_real_name(mage);
    
    if(optiondefault == 999) optiondefault = DEFAULT_OPTIONS[option];
    
    if(member_array(magename, m_indices(member_information)) == -1) {
        return optiondefault;
    }

    if(member_array("option", m_indices(member_information[magename])) == -1) {
        return optiondefault;
    }
    
    if(member_array(option, m_indices(member_information[magename]["option"])) == -1) {
        return optiondefault;
    }
    
    return member_information[magename]["option"][option];
} 
 