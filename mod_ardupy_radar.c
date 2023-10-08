//Header files for micropython.
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "shared-bindings/util.h"

//Previously mapped functions copied over.
void common_hal_falldetectionradar_construct(abstract_module_t *self);
void common_hal_falldetectionradar_deinit(abstract_module_t *self);
void common_hal_falldetectionradar_status(abstract_module_t *self, byte inf[]);

extern const mp_obj_type_t mmwave_falldetectionradar_type;

m_generic_make(falldetectionradar)
{
    abstract_module_t * self = new_abstract_module(type);
    mp_arg_check_num(n_args, n_kw, 0, 0, false);
    common_hal_falldetectionradar_construct(self);
    return self;
}

//Object attributes.
void falldetectionradar_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    abstract_module_t *self = (abstract_module_t *)self_in;
    byte number[]; //Define byte datatype.

    if(dest[0] == MP_OBJ_NULL) //Load attributes.
    {
        if(attr == MP_QSTR_Status) //Function used for Ardupy calling.
        {
            number = common_hal_falldetectionradar_Situation_judgment(self);
            dest[0] = mp_obj_new_byte(number);
            return;
        }
    }
    generic_method_lookup(self_in, attr, dest);
}

//This function takes a parameter.
mp_obj_t falldetectionradar_status(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    byte arr [] = mp_obj_get_byte(pos_args[1]);
    return mp_obj_new_byte(arr);
}
MP_DEFINE_CONST_FUN_OBJ_KW(falldetectionradar_status_obj, 1, falldetectionradar_status);

//Look-up table.
const mp_rom_map_elem_t falldetectionradar_locals_dict_table[] = {
    // instance methods
    {MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&falldetectionradar_deinit_obj)},
    {MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj)},
    {MP_ROM_QSTR(MP_QSTR___exit__), MP_ROM_PTR(&falldetectionradar_obj___exit___obj)},
    {MP_ROM_QSTR(MP_QSTR__status), MP_ROM_PTR(&falldetectionradar_status_obj)},
};

MP_DEFINE_CONST_DICT(falldetectionradar_locals_dict, falldetectionradar_locals_dict_table);

//Defining initial module type.
MP_DEFINE_CONST_DICT(bme280_locals_dict, bme280_locals_dict_table);

const mp_obj_type_t falldetection_radar_type = {
    {&mp_type_type},
    .name = MP_QSTR_falldetection_radar,
    .make_new = falldetectionradar_make_new,
    .locals_dict = (mp_obj_t)&falldetectionradar_locals_dict,
    .attr = falldetectionradar_obj_attr,
};
