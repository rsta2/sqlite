//
// kernel.cpp
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "kernel.h"

extern "C" int _main (int argc, const char **argv);

CKernel::CKernel (void)
:	CStdlibAppStdio ("06-sqlite")
{
	mActLED.Blink (5);	// show we are alive
}

CStdlibApp::TShutdownMode CKernel::Run (void)
{
        const char *pArgV[] = {GetKernelName (), nullptr};
        int nResult = _main (1, pArgV);

        mLogger.Write (GetKernelName (), LogNotice, "main() returned %d", nResult);

	return ShutdownHalt;
}
