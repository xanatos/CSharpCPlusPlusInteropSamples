using System;
using System.Runtime.InteropServices;

namespace CSharpSide
{
    public static class SafeArray
    { 
        public static void TestAll()
        {
            ReturnSafeArrayStrings();

            // In .NET Core the support for VT_RECORD has been removed,
            // so there is little support for SAFEARRAY of structs
            // see https://github.com/dotnet/runtime/issues/36603
            // C#->C++ doesn't work:
            // PassSafeArrayGuids(new Guid[5])
            // C++->C# works (unclear why)
            // ReturnSafeArrayGuids();
        }

        public static void ReturnSafeArrayStrings()
        {
            string[] strs = Native.ReturnSafeArrayStrings();

            Console.Write("C# Side, from C++, ReturnSafeArrayStrings: ");

            for (int i = 0; i < strs.Length; i++)
            {
                if (i != 0)
                {
                    Console.Write(", ");
                }

                Console.Write(strs[i]);
            }

            Console.WriteLine();
        }

        public static void ReturnSafeArrayGuids()
        {
            Guid[] guids = Native.ReturnSafeArrayGuids();

            Console.Write("C# Side, from C++, ReturnSafeArrayGuid: ");

            for (int i = 0; i < guids.Length; i++)
            {
                if (i != 0)
                {
                    Console.Write(", ");
                }

                Console.Write(guids[i]);
            }

            Console.WriteLine();
        }

        public static class Native
        {
            [DllImport(@"CPlusPlusSide")]
            [return: MarshalAs(UnmanagedType.SafeArray)]
            public static extern string[] ReturnSafeArrayStrings();

            [DllImport(@"CPlusPlusSide")]
            [return: MarshalAs(UnmanagedType.SafeArray)]
            public static extern Guid[] ReturnSafeArrayGuids();
        }
    }
}
