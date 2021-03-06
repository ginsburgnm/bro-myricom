// See the file "COPYING" in the main distribution directory for copyright.

#ifndef IOSOURCE_PKTSRC_Myricom_SOURCE_H
#define IOSOURCE_PKTSRC_Myricom_SOURCE_H

extern "C" {
#include <stdio.h>
}

#include "iosource/PktSrc.h"
#include "snf.h"
#include <errno.h>

#define SNF_F_PSHARED 0x1
#define _NSEC_PER_SEC 1000000000

namespace iosource {
namespace pktsrc {

class MyricomSource : public iosource::PktSrc {
public:
	/*
	* Constructor.
	*
	* path: Name of the interface to open.
	*
	* is_live: Must be true (the SNF source doesn't support offline operation).
	*/
	MyricomSource(const std::string& path, bool is_live);
	/*
	* Destructor.
	*/
	~MyricomSource() override;

	static PktSrc* InstantiateMyricom(const std::string& path, bool is_live);

protected:
	/* PktSrc interface */
	void Open() override;
	void Close() override;
	bool ExtractNextPacket(Packet* pkt) override;
	void DoneWithPacket() override;
	bool PrecompileFilter(int index, const std::string& filter) override;
	bool SetFilter(int index) override;
	void Statistics(Stats* stats) override;

private:
	Properties props;

	int current_filter;

	unsigned int num_received;
	unsigned int num_discarded;

	snf_handle_t snf_handle; /* opaque device handle */
	snf_ring_t   snf_ring;   /* opaque device ring handle */

	std::string  iface;
	int          ring_num;
};

}
}

#endif
