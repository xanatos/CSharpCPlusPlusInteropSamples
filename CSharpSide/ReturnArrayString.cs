using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace CSharpSide
{
    public static class ReturnArrayString
    {
        public static void TestAll()
        {
            {
                // Or use malloc in C and expose a FreeMalloc()
                string[] array = ReturnArrayString2(Native.ReturnArrayStringAnsi(out int count), count, Marshal.PtrToStringAnsi, Marshal.FreeCoTaskMem);
                Console.WriteLine($"C# Side, from C, ReturnArrayStringAnsi: {string.Join(", ", array)}");
            }

            {
                // Or use malloc in C and expose a FreeMalloc()
                string[] array = ReturnArrayString2(Native.ReturnArrayStringUnicode(out int count), count, Marshal.PtrToStringUni, Marshal.FreeCoTaskMem);
                Console.WriteLine($"C# Side, from C, ReturnArrayStringUnicode: {string.Join(", ", array)}");
            }

            {
#if NETCOREAPP
                // Or use malloc in C and expose a FreeMalloc()
                string[] array = ReturnArrayString2(Native.ReturnArrayStringUtf8(out int count), count, Marshal.PtrToStringUTF8, Marshal.FreeCoTaskMem);
#else
                // Or use malloc in C and expose a FreeMalloc()
                // Marshal.PtrToStringUTF8 isn't supported in .NET Framework
                string[] array = ReturnArrayString2(Native.ReturnArrayStringUtf8(out int count), count, Utils.PtrToStringUTF8, Marshal.FreeCoTaskMem);
#endif
                Console.WriteLine($"C# Side, from C, ReturnArrayStringUtf8: {string.Join(", ", array)}");
            }

            {
                // Or use malloc in C and expose a FreeMalloc()
                string[] array = ReturnArrayString2(Native.ReturnArrayBStr(out int count), count, Marshal.PtrToStringBSTR, Marshal.FreeBSTR);
                Console.WriteLine($"C# Side, from C, ReturnArrayBStr: {string.Join(", ", array)}");
            }

            //

            {
                string[] array = ReturnArrayStringNullTerminated(Native.ReturnArrayStringAnsiNullTerminated(), Marshal.PtrToStringAnsi, Marshal.FreeCoTaskMem);
                Console.WriteLine($"C# Side, from C, ReturnArrayStringAnsiNullTerminated: {string.Join(", ", array)}");
            }

            {
                string[] array = ReturnArrayStringNullTerminated(Native.ReturnArrayStringUnicodeNullTerminated(), Marshal.PtrToStringUni, Marshal.FreeCoTaskMem);
                Console.WriteLine($"C# Side, from C, ReturnArrayStringUnicodeNullTerminated: {string.Join(", ", array)}");
            }

            {
#if NETCOREAPP
                // Or use malloc in C and expose a FreeMalloc()
                string[] array = ReturnArrayStringNullTerminated(Native.ReturnArrayStringUtf8NullTerminated(), Marshal.PtrToStringUTF8, Marshal.FreeCoTaskMem);
#else
                // Or use malloc in C and expose a FreeMalloc()
                // Marshal.PtrToStringUTF8 isn't supported in .NET Framework
                string[] array = ReturnArrayStringNullTerminated(Native.ReturnArrayStringUtf8NullTerminated(), Utils.PtrToStringUTF8, Marshal.FreeCoTaskMem);
#endif
                Console.WriteLine($"C# Side, from C, ReturnArrayStringUtf8NullTerminated: {string.Join(", ", array)}");
            }

            {
                string[] array = ReturnArrayStringNullTerminated(Native.ReturnArrayBStrNullTerminated(), Marshal.PtrToStringBSTR, Marshal.FreeBSTR);
                Console.WriteLine($"C# Side, from C, ReturnArrayBStrNullTerminated: {string.Join(", ", array)}");
            }

            //

            {
                Native.PassOutArrayStringAnsi(out string[] array, out int count);
                Console.WriteLine($"C# Side, from C, PassOutArrayStringAnsi: {string.Join(", ", array)}");
            }

            {
                Native.PassOutArrayStringUnicode(out string[] array, out int count);
                Console.WriteLine($"C# Side, from C, PassOutArrayStringUnicode: {string.Join(", ", array)}");
            }

            // Not working, see https://github.com/dotnet/runtime/issues/7315
            //{
            //    Native.PassOutArrayStringUtf8(out string[] array, out int count);
            //    Console.WriteLine($"C# Side, from C, PassOutArrayStringUtf8: {string.Join(", ", array)}");
            //}

            {
                Native.PassOutArrayBStr(out string[] array, out int count);
                Console.WriteLine($"C# Side, from C, PassOutArrayBStr: {string.Join(", ", array)}");
            }

            //

            {
                var lst = new List<string>();
                Native.PassOutThroughDelegateArrayStringAnsi(lst.Add); // or x => lst.Add(x)
                Console.WriteLine($"C# Side, from C, PassOutThroughDelegateArrayStringAnsi: {string.Join(", ", lst)}");
            }

            {
                var lst = new List<string>();
                Native.PassOutThroughDelegateArrayStringUnicode(lst.Add); // or x => lst.Add(x)
                Console.WriteLine($"C# Side, from C, PassOutThroughDelegateArrayStringUnicode: {string.Join(", ", lst)}");
            }

            {
                var lst = new List<string>();
                Native.PassOutThroughDelegateArrayStringUtf8(lst.Add); // or x => lst.Add(x)
                Console.WriteLine($"C# Side, from C, PassOutThroughDelegateArrayStringUtf8: {string.Join(", ", lst)}");
            }

            {
                var lst = new List<string>();
                Native.PassOutThroughDelegateArrayBStr1(lst.Add); // or x => lst.Add(x)
                Console.WriteLine($"C# Side, from C, PassOutThroughDelegateArrayBStr1: {string.Join(", ", lst)}");
            }

            {
                var lst = new List<string>();
                Native.PassOutThroughDelegateArrayBStr2(lst.Add); // or x => lst.Add(x)
                Console.WriteLine($"C# Side, from C++, PassOutThroughDelegateArrayBStr2: {string.Join(", ", lst)}");
            }
        }

        public static string[] ReturnArrayString2(IntPtr ptr, int count, Func<IntPtr, string> decode, Action<IntPtr> free)
        {
            var array = new string[count];

            for (int i = 0; i < count; i++)
            {
                IntPtr ptr2 = Marshal.ReadIntPtr(ptr, i * IntPtr.Size);
                
                array[i] = decode(ptr2);

                free(ptr2);
            }

            // Or use malloc in C and expose a FreeMalloc()
            Marshal.FreeCoTaskMem(ptr);

            return array;
        }

        //

        public static string[] ReturnArrayStringNullTerminated(IntPtr ptr, Func<IntPtr, string> decode, Action<IntPtr> free)
        {
            if (ptr == IntPtr.Zero)
            {
                return new string[0];
            }

            var lst = new List<string>();

            for (int i = 0; ; i++)
            {
                IntPtr ptr2 = Marshal.ReadIntPtr(ptr, i * IntPtr.Size);

                if (ptr2 == IntPtr.Zero)
                {
                    break;
                }

                lst.Add(decode(ptr2));

                free(ptr2);
            }

            // Or use malloc in C and expose a FreeMalloc()
            Marshal.FreeCoTaskMem(ptr);

            return lst.ToArray();
        }


        public static class Native
        {
            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStringAnsi(out int count);

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStringUnicode(out int count);

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStringUtf8(out int count);

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayBStr(out int count);

            //

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStringAnsiNullTerminated();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStringUnicodeNullTerminated();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStringUtf8NullTerminated();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayBStrNullTerminated();

            //

            [DllImport(@"CSide")]
            public static extern void PassOutArrayStringAnsi([MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPStr, SizeParamIndex = 1)] out string[] array, out int count);

            [DllImport(@"CSide")]
            public static extern void PassOutArrayStringUnicode([MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPWStr, SizeParamIndex = 1)] out string[] array, out int count);

            [DllImport(@"CSide")]
            public static extern void PassOutArrayStringUtf8([MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPUTF8Str, SizeParamIndex = 1)] out string[] array, out int count);

            [DllImport(@"CSide")]
            public static extern void PassOutArrayBStr([MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.BStr, SizeParamIndex = 1)] out string[] array, out int count);

            //

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate void AddStringAnsi([MarshalAs(UnmanagedType.LPStr)] string str);

            [DllImport(@"CSide")]
            public static extern void PassOutThroughDelegateArrayStringAnsi(AddStringAnsi add);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate void AddStringUnicode([MarshalAs(UnmanagedType.LPWStr)] string str);

            [DllImport(@"CSide")]
            public static extern void PassOutThroughDelegateArrayStringUnicode(AddStringUnicode add);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate void AddStringUtf8([MarshalAs(UnmanagedType.LPUTF8Str)] string str);

            [DllImport(@"CSide")]
            public static extern void PassOutThroughDelegateArrayStringUtf8(AddStringUtf8 add);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate void AddBStr([MarshalAs(UnmanagedType.BStr)] string str);

            [DllImport(@"CSide")]
            public static extern void PassOutThroughDelegateArrayBStr1(AddBStr add);

            [DllImport(@"CPlusPlusSide")]
            public static extern void PassOutThroughDelegateArrayBStr2(AddBStr add);
        }
    }
}
