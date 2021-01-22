using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace CSharpSide
{
    public static class ReturnString
    {
        public static void TestAll()
        {
            {
                string str = Native.ReturnAnsiString();
                Console.WriteLine($"C# Side, from C, ReturnAnsiString: {str}");
            }

            {
                string str = Native.ReturnAutoString();
                Console.WriteLine($"C# Side, from C, ReturnAutoString: {str}");
            }

            {
                string str = Native.ReturnUnicodeString();
                Console.WriteLine($"C# Side, from C, ReturnUnicodeString: {str}");
            }

            {
                string str = Native.ReturnUtf8String();
                Console.WriteLine($"C# Side, from C, ReturnUtf8String: {str}");
            }

            {
                string str = Native.ReturnBStrFromChar1();
                Console.WriteLine($"C# Side, from C, ReturnBStrFromChar: {str}");
            }

            {
                string str = Native.ReturnBStrFromUtf8Char();
                Console.WriteLine($"C# Side, from C, ReturnBStrFromUtf8Char: {str}");
            }

            {
                string str = Native.ReturnBStrFromWChar1();
                Console.WriteLine($"C# Side, from C, ReturnBStrFromWChar1: {str}");
            }

            {
                string str = Native.ReturnBStrFromChar2();
                Console.WriteLine($"C# Side, from C++, ReturnBStrFromChar2: {str}");
            }

            {
                string str = Native.ReturnBStrFromChar3();
                Console.WriteLine($"C# Side, from C++, ReturnBStrFromChar3: {str}");
            }

            {
                string str = Native.ReturnBStrFromWChar2();
                Console.WriteLine($"C# Side, from C++, ReturnBStrFromWChar2: {str}");
            }

            {
                string str = ReturnAnsiStringPtrMalloc();
                Console.WriteLine($"C# Side, from C, ReturnAnsiStringPtrMalloc: {str}");
            }

            {
                string str = ReturnUnicodeStringPtrMalloc();
                Console.WriteLine($"C# Side, from C, ReturnUnicodeStringPtrMalloc: {str}");
            }

            {
                string str = ReturnUtf8StringPtrMalloc();
                Console.WriteLine($"C# Side, from C, ReturnUtf8StringPtrMalloc: {str}");
            }

            {
                string str = ReturnAnsiStringPtrNoFree();
                Console.WriteLine($"C# Side, from C, ReturnAnsiStringPtrNoFree: {str}");
            }

            {
                string str = ReturnUnicodeStringPtrNoFree();
                Console.WriteLine($"C# Side, from C, ReturnUnicodeStringPtrNoFree: {str}");
            }

            {
                string str = ReturnUtf8StringPtrNoFree();
                Console.WriteLine($"C# Side, from C, ReturnUtf8StringPtrNoFree: {str}");
            }
        }

        public static string ReturnAnsiStringPtrMalloc()
        {
            IntPtr ptr = IntPtr.Zero;

            try
            {
                ptr = Native.ReturnAnsiStringPtrMalloc();

                string str = Marshal.PtrToStringAnsi(ptr);
                return str;
            }

            finally
            {
                if (ptr != IntPtr.Zero)
                {
                    Utils.Native.FreeMalloc(ptr);
                }
            }
        }

        public static string ReturnUnicodeStringPtrMalloc()
        {
            IntPtr ptr = IntPtr.Zero;

            try
            {
                ptr = Native.ReturnUnicodeStringPtrMalloc();

                string str = Marshal.PtrToStringUni(ptr);
                return str;
            }

            finally
            {
                if (ptr != IntPtr.Zero)
                {
                    Utils.Native.FreeMalloc(ptr);
                }
            }
        }

        public static string ReturnUtf8StringPtrMalloc()
        {
            IntPtr ptr = IntPtr.Zero;

            try
            {
                ptr = Native.ReturnUtf8StringPtrMalloc();

#if NETCOREAPP
                string str = Marshal.PtrToStringUTF8(ptr);
#else
                // Marshal.PtrToStringUTF8 isn't supported in .NET Framework
                string str = Utils.PtrToStringUTF8(ptr);
#endif

                return str;
            }

            finally
            {
                if (ptr != IntPtr.Zero)
                {
                    Utils.Native.FreeMalloc(ptr);
                }
            }
        }

        public static string ReturnAnsiStringPtrNoFree()
        {
            IntPtr ptr = Native.ReturnAnsiStringPtrNoFree();
            string str = Marshal.PtrToStringAnsi(ptr);
            return str;
        }

        public static string ReturnUnicodeStringPtrNoFree()
        {
            IntPtr ptr = Native.ReturnUnicodeStringPtrNoFree();
            string str = Marshal.PtrToStringUni(ptr);
            return str;
        }

        public static string ReturnUtf8StringPtrNoFree()
        {
            IntPtr ptr = Native.ReturnUtf8StringPtrNoFree();

#if NETCOREAPP
            string str = Marshal.PtrToStringUTF8(ptr);
#else
            // Marshal.PtrToStringUTF8 isn't supported in .NET Framework
            string str = Utils.PtrToStringUTF8(ptr);
#endif

            return str;
        }

        public static class Native
        {
            [DllImport(@"CSide")]
            [return: MarshalAs(UnmanagedType.LPStr)]
            public static extern string ReturnAnsiString();

            [DllImport(@"CSide")]
            [return: MarshalAs(UnmanagedType.LPTStr)]
            public static extern string ReturnAutoString();

            [DllImport(@"CSide")]
            [return: MarshalAs(UnmanagedType.LPWStr)]
            public static extern string ReturnUnicodeString();

            [DllImport(@"CSide")]
            [return: MarshalAs(UnmanagedType.LPUTF8Str)]
            public static extern string ReturnUtf8String();

            [DllImport(@"CSide")]
            [return: MarshalAs(UnmanagedType.BStr)]
            public static extern string ReturnBStrFromChar1();

            [DllImport(@"CSide")]
            [return: MarshalAs(UnmanagedType.BStr)]
            public static extern string ReturnBStrFromUtf8Char();

            [DllImport(@"CSide")]
            [return: MarshalAs(UnmanagedType.BStr)]
            public static extern string ReturnBStrFromWChar1();

            [DllImport(@"CPlusPlusSide")]
            [return: MarshalAs(UnmanagedType.BStr)]
            public static extern string ReturnBStrFromChar2();

            [DllImport(@"CPlusPlusSide")]
            [return: MarshalAs(UnmanagedType.BStr)]
            public static extern string ReturnBStrFromChar3();

            [DllImport(@"CPlusPlusSide")]
            [return: MarshalAs(UnmanagedType.BStr)]
            public static extern string ReturnBStrFromWChar2();

            //

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnAnsiStringPtrMalloc();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnUnicodeStringPtrMalloc();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnUtf8StringPtrMalloc();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnAnsiStringPtrNoFree();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnUnicodeStringPtrNoFree();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnUtf8StringPtrNoFree();
        }
    }
}
