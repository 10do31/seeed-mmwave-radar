#include "Seeed_Arduino_falldetectionradar/falldetectionradar.h" //Include dependent Arduino library.

extern "C" //Tells compiler to use the C naming and calling conventions.
{
    //Header files for micropython.
    #include "py/mphal.h"
    #include "py/nlr.h"
    #include "py/objtype.h"
    #include "py/runtime.h"
    #include "py/shared-bindings/util.h"
}

//Initialize module.
#define falldetectionradar (*(FALLDETECTIONRADAR *)self->module)
void *operator new(size_t, void *);

//Map functions from dependendent library.
extern "C"
{
    void common_hal_falldetectionradar_construct(abstract_module_t *self)
    {
        self->module = new (m_new_obj(FALLDETECTIONRADAR)) FALLDETECTIONRADAR();
        falldetectionradar.SerialInit(); // Start the sensor.
    }

    void common_hal_falldetectionradar_deinit(abstract_module_t *self)
    {
        falldetectionradar.~FALLDETECTIONRADAR();
    }

    void common_hal_falldetectionradar_status(abstract_module_t *self, byte arr[])
    {
        return falldetectionradar.Situation_judgement(arr[]);
    }   
}
