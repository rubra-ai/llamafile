gmake -j8 && sudo gmake install PREFIX=/usr/local

# download model if it hasn't been downloaded yet
# Mistral-7B-Instruct-v0.3-Q6_K.gguf
# rubra-Mistral-7B-Instruct-v0.2-fc-json_v1-v6.gguf
if [ ! -f "rubra-Mistral-7B-Instruct-v0.2-fc-json_v1-v6.gguf" ]; then
    wget "https://huggingface.co/yingbei/rubra-Mistral-7B-Instruct-v0.2-fc-json_v1-v6.gguf/resolve/main/rubra-Mistral-7B-Instruct-v0.2-fc-json_v1-v6.gguf"
fi

# copy the base llamafile
cp /usr/local/bin/llamafile rubra.llamafile
cp .args_llm .args
# package everything up
zipalign -j0 \
  rubra.llamafile \
  rubra-Mistral-7B-Instruct-v0.2-fc-json_v1-v6.gguf \
  .args

rm .args

## run it
# ./rubra.llamafile
