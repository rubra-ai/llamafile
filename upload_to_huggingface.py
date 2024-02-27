from huggingface_hub import HfApi, login
login()
api = HfApi()

# upload Rubra llamafile
# api.upload_file(
#     path_or_fileobj="./rubra.llamafile",
#     path_in_repo="rubra.llamafile",
#     repo_id="rubra-ai/rubra-llamafile",
#     repo_type="model",
# )

# upload raw compiled llamafile
# api.upload_file(
#     path_or_fileobj="/usr/local/bin/llamafile",
#     path_in_repo="llamafile",
#     repo_id="rubra-ai/rubra-llamafile",
#     repo_type="model",
# )

# upload the raw model
api.upload_file(
    path_or_fileobj="./openhermes-2.5-neural-chat-v3-3-slerp.Q6_K.gguf",
    path_in_repo="openhermes-2.5-neural-chat-v3-3-slerp.Q6_K.gguf",
    repo_id="rubra-ai/rubra-llamafile",
    repo_type="model",
)