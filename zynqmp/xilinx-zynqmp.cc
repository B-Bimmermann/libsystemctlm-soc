/*
 Xilinx SystemC/TLM-2.0 ZynqMP Wrapper.

 Written by Edgar E. Iglesias <edgar.iglesias@xilinx.com>

 Copyright (c) 2016, Xilinx Inc.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <inttypes.h>

#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/tlm_quantumkeeper.h"

using namespace sc_core;
using namespace std;

extern "C" {
#include "safeio.h"
#include "remote-port-proto.h"
#include "remote-port-sk.h"
};
#include "xilinx-zynqmp.h"
#include <sys/types.h>

xilinx_zynqmp::xilinx_zynqmp(sc_module_name name, const char *sk_descr)
	: remoteport_tlm(name, -1, sk_descr),
	  rp_axi_hpm0_fpd("rp_axi_hpm0_fpd"),
	  rp_axi_hpm1_fpd("rp_axi_hpm1_fpd"),
	  rp_axi_hpm_lpd("rp_axi_hpm_lpd"),
	  rp_axi_hpc0_fpd("rp_axi_hpc0_fpd"),
	  rp_axi_hpc1_fpd("rp_axi_hpc1_fpd"),
	  rp_axi_hp0_fpd("rp_axi_hp0_fpd"),
	  rp_axi_hp1_fpd("rp_axi_hp1_fpd"),
	  rp_axi_hp2_fpd("rp_axi_hp2_fpd"),
	  rp_axi_hp3_fpd("rp_axi_hp3_fpd"),
	  rp_axi_lpd("rp_axi_lpd"),
	  rp_axi_acp_fpd("rp_axi_acp_fpd"),
	  rp_axi_ace_fpd("rp_axi_ace_fpd"),
	  rp_wires_in("wires_in", 16, 0),
	  rp_wires_out("wires_out", 0, 4),
	  rp_irq_out("irq_out", 0, 164),
	  pl2ps_irq("pl2ps_irq", 16),
	  ps2pl_irq("ps2pl_irq", 164)
{
	int i;

	/* Expose friendly named PS Master ports.  */
	s_axi_hpm_fpd[0] = &rp_axi_hpm0_fpd.sk;
	s_axi_hpm_fpd[1] = &rp_axi_hpm1_fpd.sk;
	s_axi_hpm_lpd = &rp_axi_hpm_lpd.sk;

	/* Expose friendly named PL Master ports.  */
	s_axi_hpc_fpd[0] = &rp_axi_hpc0_fpd.sk;
	s_axi_hpc_fpd[1] = &rp_axi_hpc1_fpd.sk;
	s_axi_hp_fpd[0] = &rp_axi_hp0_fpd.sk;
	s_axi_hp_fpd[1] = &rp_axi_hp1_fpd.sk;
	s_axi_hp_fpd[2] = &rp_axi_hp2_fpd.sk;
	s_axi_hp_fpd[3] = &rp_axi_hp3_fpd.sk;
	s_axi_lpd = &rp_axi_lpd.sk;
	s_axi_acp_fpd = &rp_axi_acp_fpd.sk;
	s_axi_ace_fpd = &rp_axi_ace_fpd.sk;

	for (i = 0; i < 16; i++) {
		rp_wires_in.wires_in[i](pl2ps_irq[i]);
	}

	for (i = 0; i < 164; i++) {
		rp_irq_out.wires_out[i](ps2pl_irq[i]);
	}

	register_dev(0, &rp_axi_hpc0_fpd);
	register_dev(1, &rp_axi_hpc1_fpd);
	register_dev(2, &rp_axi_hp0_fpd);
	register_dev(3, &rp_axi_hp1_fpd);
	register_dev(4, &rp_axi_hp2_fpd);
	register_dev(5, &rp_axi_hp3_fpd);
	register_dev(6, &rp_axi_lpd);
	register_dev(7, &rp_axi_acp_fpd);
	register_dev(8, &rp_axi_ace_fpd);

	register_dev(9, &rp_axi_hpm0_fpd);
	register_dev(10, &rp_axi_hpm1_fpd);
	register_dev(11, &rp_axi_hpm_lpd);

	register_dev(12, &rp_wires_in);
	register_dev(13, &rp_wires_out);
	register_dev(14, &rp_irq_out);
}