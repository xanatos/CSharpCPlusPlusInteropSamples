using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace CSharpSide
{
    public static class ReturnArrayStruct
    {
        public static void TestAll()
        {
            {
                Native.StructStringAnsiInt[] array = ReturnArrayStruct2<Native.StructStringAnsiInt>(Native.ReturnArrayStructStringAnsiInt(out int count), count);
                Console.WriteLine($"C# Side, from C, ReturnArrayStructStringAnsiInt: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            {
                Native.StructStringUnicodeInt[] array = ReturnArrayStruct2<Native.StructStringUnicodeInt>(Native.ReturnArrayStructStringUnicodeInt(out int count), count);
                Console.WriteLine($"C# Side, from C, ReturnArrayStructStringUnicodeInt: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

#if NETCOREAPP
            {
                // Not working on .NET Framework, not backported: https://github.com/dotnet/runtime/issues/11968
                Native.StructStringUtf8Int[] array = ReturnArrayStruct2<Native.StructStringUtf8Int>(Native.ReturnArrayStructStringUtf8Int(out int count), count);
                Console.WriteLine($"C# Side, from C, ReturnArrayStructStringUtf8Int: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }
#endif

            {
                Native.StructBStrInt[] array = ReturnArrayStruct2<Native.StructBStrInt>(Native.ReturnArrayStructBStrInt(out int count), count);
                Console.WriteLine($"C# Side, from C, ReturnArrayStructBStrInt: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            //

            {
                Native.ClassStringAnsiInt[] array = ReturnArrayPtrStruct<Native.ClassStringAnsiInt>(Native.ReturnArrayPtrStructStringAnsiInt(out int count), count);
                Console.WriteLine($"C# Side, from C, ReturnArrayPtrStructStringAnsiInt: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            {
                Native.ClassStringUnicodeInt[] array = ReturnArrayPtrStruct<Native.ClassStringUnicodeInt>(Native.ReturnArrayPtrStructStringUnicodeInt(out int count), count);
                Console.WriteLine($"C# Side, from C, ReturnArrayPtrStructStringUnicodeInt: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

#if NETCOREAPP
            {
                // Not working on .NET Framework, not backported: https://github.com/dotnet/runtime/issues/11968
                Native.ClassStringUtf8Int[] array = ReturnArrayPtrStruct<Native.ClassStringUtf8Int>(Native.ReturnArrayPtrStructStringUtf8Int(out int count), count);
                Console.WriteLine($"C# Side, from C, ReturnArrayPtrStructStringUtf8Int: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }
#endif

            {
                Native.ClassBStrInt[] array = ReturnArrayPtrStruct<Native.ClassBStrInt>(Native.ReturnArrayPtrStructBStrInt(out int count), count);
                Console.WriteLine($"C# Side, from C, ReturnArrayPtrStructBStrInt: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            //

            {
                Native.ClassStringAnsiInt[] array = ReturnArrayPtrStructNullTerminated<Native.ClassStringAnsiInt>(Native.ReturnArrayPtrStructStringAnsiIntNullTerminated());
                Console.WriteLine($"C# Side, from C, ReturnArrayPtrStructStringAnsiIntNullTerminated: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            {
                Native.ClassStringUnicodeInt[] array = ReturnArrayPtrStructNullTerminated<Native.ClassStringUnicodeInt>(Native.ReturnArrayPtrStructStringUnicodeIntNullTerminated());
                Console.WriteLine($"C# Side, from C, ReturnArrayPtrStructStringUnicodeIntNullTerminated: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

#if NETCOREAPP
            {
                // Not working on .NET Framework, not backported: https://github.com/dotnet/runtime/issues/11968
                Native.ClassStringUtf8Int[] array = ReturnArrayPtrStructNullTerminated<Native.ClassStringUtf8Int>(Native.ReturnArrayPtrStructStringUtf8IntNullTerminated());
                Console.WriteLine($"C# Side, from C, ReturnArrayPtrStructStringUtf8IntNullTerminated: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }
#endif
            {
                Native.ClassBStrInt[] array = ReturnArrayPtrStructNullTerminated<Native.ClassBStrInt>(Native.ReturnArrayPtrStructBStrIntNullTerminated());
                Console.WriteLine($"C# Side, from C, ReturnArrayPtrStructBStrIntNullTerminated: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            //

            {
                Native.PassOutArrayStructStringAnsiInt(out Native.StructStringAnsiInt[] array, out int count);
                Console.WriteLine($"C# Side, from C, PassOutArrayStructStringAnsiInt: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            {
                Native.PassOutArrayStructStringUnicodeInt(out Native.StructStringUnicodeInt[] array, out int count);
                Console.WriteLine($"C# Side, from C, PassOutArrayStructStringUnicodeInt: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

#if NETCORE
            {
                // Not supported on .NET Framework
                Native.PassOutArrayStructStringUtf8Int(out Native.StructStringUtf8Int[] array, out int count);
                Console.WriteLine($"C# Side, from C, PassOutArrayStructStringUtf8Int: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }
#endif

            {
                Native.PassOutArrayStructBStrInt(out Native.StructBStrInt[] array, out int count);
                Console.WriteLine($"C# Side, from C, PassOutArrayStructBStrInt: {string.Join(", ", array.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            //

            {
                var lst = new List<StructStringInt>();
                Native.PassOutThroughDelegateArrayStructStringAnsiInt((str, num) => lst.Add(new StructStringInt { Str = str, Num = num }));
                Console.WriteLine($"C# Side, from C, PassOutThroughDelegateArrayStructStringAnsiInt: {string.Join(", ", lst.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            {
                var lst = new List<StructStringInt>();
                Native.PassOutThroughDelegateArrayStructStringUnicodeInt((str, num) => lst.Add(new StructStringInt { Str = str, Num = num }));
                Console.WriteLine($"C# Side, from C, PassOutThroughDelegateArrayStructStringUnicodeInt: {string.Join(", ", lst.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            {
                var lst = new List<StructStringInt>();
                Native.PassOutThroughDelegateArrayStructStringUtf8Int((str, num) => lst.Add(new StructStringInt { Str = str, Num = num })); ;
                Console.WriteLine($"C# Side, from C, PassOutThroughDelegateArrayStructStringUtf8Int: {string.Join(", ", lst.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            {
                var lst = new List<StructStringInt>();
                Native.PassOutThroughDelegateArrayStructBStrInt1((str, num) => lst.Add(new StructStringInt { Str = str, Num = num })); ;
                Console.WriteLine($"C# Side, from C, PassOutThroughDelegateArrayStructBStrInt1: {string.Join(", ", lst.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }

            {
                var lst = new List<StructStringInt>();
                Native.PassOutThroughDelegateArrayStructBStrInt2((str, num) => lst.Add(new StructStringInt { Str = str, Num = num })); ;
                Console.WriteLine($"C# Side, from C++, PassOutThroughDelegateArrayStructBStrInt2: {string.Join(", ", lst.Select(x => $"[{x.Str}, {x.Num}]"))}");
            }
        }

        //

        public static T[] ReturnArrayStruct2<T>(IntPtr ptr, int count) where T : struct
        {
            var array = new T[count];

            int size = Marshal.SizeOf<T>();

            for (int i = 0; i < count; i++)
            {
                IntPtr ptr2 = ptr + (i * size);
                array[i] = Marshal.PtrToStructure<T>(ptr2);
                // This will call CoTaskMemFree for the string!
                Marshal.DestroyStructure<T>(ptr2);
            }

            // Or use malloc in C and expose a FreeMalloc()
            Marshal.FreeCoTaskMem(ptr);

            return array;
        }

        //

        public static T[] ReturnArrayPtrStruct<T>(IntPtr ptr, int count) where T : class
        {
            var array = new T[count];

            for (int i = 0; i < count; i++)
            {
                IntPtr ptr2 = Marshal.ReadIntPtr(ptr, i * IntPtr.Size);
                array[i] = Marshal.PtrToStructure<T>(ptr2);

                // This will call CoTaskMemFree for the string
                Marshal.DestroyStructure<T>(ptr2);
                // And this will call CoTaskMemFree for the struct
                Marshal.FreeCoTaskMem(ptr2);
            }

            // Or use malloc in C and expose a FreeMalloc()
            Marshal.FreeCoTaskMem(ptr);

            return array;
        }

        //

        public static T[] ReturnArrayPtrStructNullTerminated<T>(IntPtr ptr) where T : class
        {

            if (ptr == IntPtr.Zero)
            {
                return new T[0];
            }

            var lst = new List<T>();

            for (int i = 0; ; i++)
            {
                IntPtr ptr2 = Marshal.ReadIntPtr(ptr, i * IntPtr.Size);

                if (ptr2 == IntPtr.Zero)
                {
                    break;
                }

                lst.Add(Marshal.PtrToStructure<T>(ptr2));

                // This will call CoTaskMemFree for the string
                Marshal.DestroyStructure<T>(ptr2);
                // And this will call CoTaskMemFree for the struct
                Marshal.FreeCoTaskMem(ptr2);
            }

            // Or use malloc in C and expose a FreeMalloc()
            Marshal.FreeCoTaskMem(ptr);

            return lst.ToArray();
        }

        //

        // Not for marshalling
        public struct StructStringInt
        {
            public string Str;

            public int Num;
        }

        //

        public static class Native
        {
            [StructLayout(LayoutKind.Sequential)]
            public struct StructStringAnsiInt
            {
                [MarshalAs(UnmanagedType.LPStr)]
                public string Str;

                public int Num;
            }

            [StructLayout(LayoutKind.Sequential)]
            public struct StructStringUnicodeInt
            {
                [MarshalAs(UnmanagedType.LPWStr)]
                public string Str;

                public int Num;
            }

            [StructLayout(LayoutKind.Sequential)]
            public struct StructStringUtf8Int
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                public string Str;

                public int Num;
            }

            [StructLayout(LayoutKind.Sequential)]
            public struct StructBStrInt
            {
                [MarshalAs(UnmanagedType.BStr)]
                public string Str;

                public int Num;
            }

            //

            // A pointer to a struct is a class :-)
            [StructLayout(LayoutKind.Sequential)]
            public class ClassStringAnsiInt
            {
                [MarshalAs(UnmanagedType.LPStr)]
                public string Str;

                public int Num;
            }

            // A pointer to a struct is a class :-)
            [StructLayout(LayoutKind.Sequential)]
            public class ClassStringUnicodeInt
            {
                [MarshalAs(UnmanagedType.LPWStr)]
                public string Str;

                public int Num;
            }

            // A pointer to a struct is a class :-)
            [StructLayout(LayoutKind.Sequential)]
            public class ClassStringUtf8Int
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                public string Str;

                public int Num;
            }

            // A pointer to a struct is a class :-)
            [StructLayout(LayoutKind.Sequential)]
            public class ClassBStrInt
            {
                [MarshalAs(UnmanagedType.BStr)]
                public string Str;

                public int Num;
            }

            //

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStructStringAnsiInt(out int count);

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStructStringUnicodeInt(out int count);

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStructStringUtf8Int(out int count);

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayStructBStrInt(out int count);

            //

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayPtrStructStringAnsiInt(out int count);

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayPtrStructStringUnicodeInt(out int count);

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayPtrStructStringUtf8Int(out int count);

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayPtrStructBStrInt(out int count);

            //

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayPtrStructStringAnsiIntNullTerminated();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayPtrStructStringUnicodeIntNullTerminated();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayPtrStructStringUtf8IntNullTerminated();

            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayPtrStructBStrIntNullTerminated();

            //

            [DllImport(@"CSide")]
            public static extern void PassOutArrayStructStringAnsiInt([MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] out StructStringAnsiInt[] array, out int count);

            [DllImport(@"CSide")]
            public static extern void PassOutArrayStructStringUnicodeInt([MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] out StructStringUnicodeInt[] array, out int count);

            [DllImport(@"CSide")]
            public static extern void PassOutArrayStructStringUtf8Int([MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] out StructStringUtf8Int[] array, out int count);

            [DllImport(@"CSide")]
            public static extern void PassOutArrayStructBStrInt([MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] out StructBStrInt[] array, out int count);

            //

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate void StringAnsiInt([MarshalAs(UnmanagedType.LPStr)] string str, int num);

            [DllImport(@"CSide")]
            public static extern void PassOutThroughDelegateArrayStructStringAnsiInt(StringAnsiInt add);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate void StringUnicodeInt([MarshalAs(UnmanagedType.LPWStr)] string str, int num);

            [DllImport(@"CSide")]
            public static extern void PassOutThroughDelegateArrayStructStringUnicodeInt(StringUnicodeInt add);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate void StringUtf8Int([MarshalAs(UnmanagedType.LPUTF8Str)] string str, int num);

            [DllImport(@"CSide")]
            public static extern void PassOutThroughDelegateArrayStructStringUtf8Int(StringUtf8Int add);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate void BStrInt([MarshalAs(UnmanagedType.BStr)] string str, int num);

            [DllImport(@"CSide")]
            public static extern void PassOutThroughDelegateArrayStructBStrInt1(BStrInt add);

            [DllImport(@"CPlusPlusSide")]
            public static extern void PassOutThroughDelegateArrayStructBStrInt2(BStrInt add);
        }
    }
}
