using System;
using System.Runtime.InteropServices;
using System.Text;

namespace CSharpSide
{
    public static class PassString
    {
        public static void TestAll()
        {
            var strs = new[] { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };

            Native.PrintAnsiString("Foo àèéìòù āēīōū");

            Native.PrintUtf8String("Bar àèéìòù āēīōū");

            Native.PrintUnicodeString("Baz àèéìòù āēīōū");

            Native.PrintAutoString("Qux àèéìòù āēīōū");

            Native.PrintBStr("Quux àèéìòù āēīōū");

            PrintArrayStringRef(strs);

            Native.PrintArray(strs, strs.Length);

            PrintArrayNullTerminated(strs);
        }

        public static void PrintArrayNullTerminated(string[] strs)
        {
            // Null-terminated array (the last element MUST be null)
            string[] strsPlusNull = strs;

            Array.Resize(ref strsPlusNull, strsPlusNull.Length + 1);

            Native.PrintArrayNullTerminated(strsPlusNull);
        }

        public static void PrintArrayStringRef(params string[] strings)
        {
            var ansis = Array.ConvertAll(strings, x => Encoding.Default.GetBytes(x));
            var handles = new GCHandle[ansis.Length];
            var refs = new Native.StringRef[ansis.Length];

            try
            {
                for (int i = 0; i < handles.Length; i++)
                {
                    try
                    {
                    }
                    finally
                    {
                        handles[i] = GCHandle.Alloc(ansis[i], GCHandleType.Pinned);
                    }

                    refs[i] = new Native.StringRef
                    {
                        PBytes = handles[i].AddrOfPinnedObject(),
                        Length = ansis[i].Length
                    };
                }

                Native.PrintArrayStringRef(refs, refs.Length);
            }
            finally
            {
                for (int i = 0; i < handles.Length; i++)
                {
                    if (handles[i].IsAllocated)
                    {
                        handles[i].Free();
                    }
                }
            }
        }

        public static class Native
        {
            [DllImport(@"CSide")]
            public static extern void PrintAnsiString([MarshalAs(UnmanagedType.LPStr)] string str);

            [DllImport(@"CSide")]
            public static extern void PrintUtf8String([MarshalAs(UnmanagedType.LPUTF8Str)] string str);

            [DllImport(@"CSide")]
            public static extern void PrintUnicodeString([MarshalAs(UnmanagedType.LPWStr)] string str);

            [DllImport(@"CSide")]
            public static extern void PrintAutoString([MarshalAs(UnmanagedType.LPTStr)] string str);

            [DllImport(@"CSide")]
            public static extern void PrintBStr([MarshalAs(UnmanagedType.BStr)] string str);

            [DllImport(@"CSide")]
            public static extern void PrintArrayStringRef(StringRef[] array, int count);

            [StructLayout(LayoutKind.Sequential)]
            public struct StringRef
            {
                public IntPtr PBytes;
                public int Length;
            }

            [DllImport(@"CSide")]
            public static extern void PrintArray([MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPStr)] string[] array, int count);

            // Null-terminated array (the last element MUST be null)
            [DllImport(@"CSide")]
            public static extern void PrintArrayNullTerminated([MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPStr)] string[] array);
        }
    }
}
