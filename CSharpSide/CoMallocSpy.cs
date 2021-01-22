using System;
using System.Runtime.InteropServices;

namespace CSharpSide
{
    public static class CoMallocSpy
    {
        public static class Native
        {
            [DllImport("OleAut32")]
            public static extern void SetOaNoCache();

            [DllImport(@"CPlusPlusSide", EntryPoint = "StartMallocSpy")]
            public static extern Spy Start();

            [DllImport(@"CPlusPlusSide")]
            public static extern void SetBreakAlloc(Spy spy, int allocNum);

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            public delegate void Print([MarshalAs(UnmanagedType.LPWStr)] string str);

            [DllImport(@"CPlusPlusSide", EntryPoint = "DumpMallocSpy")]
            public static extern void Dump(Spy spy, Print print);

            [DllImport(@"CPlusPlusSide", EntryPoint = "StopMallocSpy")]
            [return: MarshalAs(UnmanagedType.I1)]
            public static extern bool Stop();

            public struct Spy
            {
                public IntPtr ptr;
            }
        }
    }
}
