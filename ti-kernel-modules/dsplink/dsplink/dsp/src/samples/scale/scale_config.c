/** ============================================================================
 *  @file   scale_config.c
 *
 *  @path   $(DSPLINK)/dsp/src/samples/scale/
 *
 *  @desc   Source file containing configuration for the SCALE sample.
 *
 *  @ver    1.65.01.05_eng
 *  ============================================================================
 *  Copyright (C) 2002-2009, Texas Instruments Incorporated -
 *  http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  ============================================================================
 */


/*  ----------------------------------- DSP/BIOS Headers            */
#include <std.h>
#include <sys.h>
#include <msgq.h>
#include <pool.h>

/*  ----------------------------------- DSP/BIOS LINK Headers       */
#include <dsplink.h>
#include <failure.h>

#if defined (MSGQ_ZCPY_LINK)
#include <zcpy_mqt.h>
#endif /* if defined (MSGQ_ZCPY_LINK) */

#if defined (ZCPY_LINK)
#if ((PHYINTERFACE == PCI_INTERFACE) || (PHYINTERFACE == VLYNQ_INTERFACE))
#include <dma_pool.h>
#else
#include <sma_pool.h>
#endif /* if ((PHYINTERFACE == PCI_INTERFACE) || (PHYINTERFACE == VLYNQ_INTERFACE)) */
#endif /* if defined (ZCPY_LINK) */

/*  ----------------------------------- Sample Headers              */
#include <scale_config.h>
#if defined (DSP_BOOTMODE_NOBOOT)
#include <dsplinkmsgq.h>
#endif

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  @const  NUM_POOLS
 *
 *  @desc   Number of pools configured in the system.
 *  ============================================================================
 */
#define NUM_POOLS           1

/** ============================================================================
 *  @const  NUM_MSG_QUEUES
 *
 *  @desc   Number of local message queues
 *  ============================================================================
 */
#define NUM_MSG_QUEUES      1


/** ============================================================================
 *  @const  SAMPLEPOOL_PARAMS, SAMPLEPOOL_FXNS, SAMPLEPOOL_init
 *
 *  @desc   Pool configuration definitions
 *  ============================================================================
 */
#define SAMPLEMQT_FXNS          ZCPYMQT_FXNS
#define SAMPLEMQT_init          ZCPYMQT_init
#define SAMPLEMQT_CTRLMSG_SIZE  ZCPYMQT_CTRLMSG_SIZE
ZCPYMQT_Params  mqtParams = {SAMPLE_POOL_ID} ;
#define SAMPLEPOOL_PARAMS       SamplePoolParams
#if ((PHYINTERFACE == PCI_INTERFACE) || (PHYINTERFACE == VLYNQ_INTERFACE))
#define SAMPLEPOOL_FXNS         DMAPOOL_FXNS
#define SAMPLEPOOL_INIT         DMAPOOL_init

DMAPOOL_Params SamplePoolParams =
{
    SAMPLE_POOL_ID, /* Pool ID */
    TRUE            /* Exact Size Match Requirement */
} ;
#else
#define SAMPLEPOOL_FXNS         SMAPOOL_FXNS
#define SAMPLEPOOL_INIT         SMAPOOL_init

SMAPOOL_Params SamplePoolParams =
{
    SAMPLE_POOL_ID, /* Pool ID */
    TRUE            /* Exact Size Match Requirement */
} ;
#endif /* if ((PHYINTERFACE == PCI_INTERFACE) || (PHYINTERFACE == VLYNQ_INTERFACE)) */




/** ============================================================================
 *  @name   msgQueues
 *
 *  @desc   Array of local message queues
 *  ============================================================================
 */
static MSGQ_Obj msgQueues [NUM_MSG_QUEUES] ;


/** ============================================================================
 *  @name   transports
 *
 *  @desc   Array of transports.
 *  ============================================================================
 */
MSGQ_TransportObj transports [MAX_PROCESSORS] =
{
#if (MAX_PROCESSORS == 2) /* one DSP and one GPP processor */
     MSGQ_NOTRANSPORT,    /* Represents the local processor */
#elif (MAX_PROCESSORS == 3 ) /* TWO DSPs and one GPP processor */
     MSGQ_NOTRANSPORT,
     MSGQ_NOTRANSPORT,
#else
#error ****ERROR:transports need to be defined for MAX_PROCESSORS
#endif
#if defined (DSP_BOOTMODE_NOBOOT)
     MSGQ_NOTRANSPORT,    /* Represents the local processor */
#else
     {
        &SAMPLEMQT_init,  /* Init Function                 */
        &SAMPLEMQT_FXNS,  /* Transport interface functions */
        &mqtParams,       /* Transport params              */
        NULL,             /* Filled in by transport        */
        ID_GPP            /* Processor Id                  */
     }
#endif
} ;

/** ============================================================================
 *  @name   MSGQ_config
 *
 *  @desc   MSGQ configuration information.
 *          MSGQ_config is a required global variable.
 *  ============================================================================
 */
MSGQ_Config MSGQ_config =
{
    msgQueues,
    transports,
    NUM_MSG_QUEUES,
    MAX_PROCESSORS,
    0,
    MSGQ_INVALIDMSGQ,
    POOL_INVALIDID
} ;


/** ============================================================================
 *  @name   SCALE_Pools
 *
 *  @desc   Array of pools.
 *  ============================================================================
 */
POOL_Obj SCALE_Pools [NUM_POOLS] =
{
#if defined (DSP_BOOTMODE_NOBOOT)
	POOL_NOENTRY
#else
    {
        &SAMPLEPOOL_INIT,               /* Init Function                      */
        (POOL_Fxns *) &SAMPLEPOOL_FXNS, /* Pool interface functions           */
        &SAMPLEPOOL_PARAMS,              /* Pool params                        */
        NULL                            /* Pool object: Set within pool impl. */
    }
#endif
} ;

/** ============================================================================
 *  @name   POOL_config
 *
 *  @desc   POOL configuration information.
 *          POOL_config is a required global variable.
 *  ============================================================================
 */
POOL_Config POOL_config = {SCALE_Pools, NUM_POOLS} ;


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
